
#define _GNU_SOURCE
#include <stdio.h>
#undef _GNU_SOURCE

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "logger.h"
#include "tree.h"
#include "utils.h"

#ifdef __DEBUG__
#define _clk_dir "/home/shmily/bogon/clockTree/clk"
#else
#define _clk_dir "/sys/kernel/debug/clk"
#endif

struct clock_info {
	int flags;
	unsigned int rate;
	int usecount;
	bool expanded;
	char *prefix;
	int preparecount;
	int notifiercount;
};

struct route_info {
	char *path;
	char *name;
};

struct tree *clock_tree;

int clock_dir_scan(struct tree *tree);
int fill_clock_tree(void);

int main(void)
{
	struct route_info *ri;

	printf("%*s%s\n", 12, "-", "clk");

	ri = malloc(sizeof(*ri));
	if (!ri) {
		log_err("route_info, malloc faild\n");
		return -1;
	}

	ri->path = _clk_dir;
	clock_tree = tree_alloc(ri, 0);
	if (!clock_tree)
		return -1;

	if (clock_dir_scan(clock_tree)) {
		log_err("scan %s faild\n", ri->path);
		free(ri);
		tree_free(clock_tree);
		return -1;
	}

	fill_clock_tree();

	return 0;
}

/*
 * sacn the clk dir, and build the clock tree.
 */
int clock_dir_scan(struct tree *tree)
{
	int ret;
	DIR *dir;
	char *basedir, *newpath;
	struct stat s;
	struct dirent dirent, *direntp;

	log_inf("try to scan directory %s\n", ((struct route_info *)tree->route)->path);
	dir = opendir(((struct route_info *)tree->route)->path);
	if (!dir) {
		log_err("unable to open directory %s\n",
			((struct route_info *)tree->route)->path);
		return -1;
	}

	while (!readdir_r(dir, &dirent, &direntp)) {
		struct tree *child;
		struct route_info *ri;

		if (!direntp) break;
		if (direntp->d_name[0]=='.') continue;

		ret = asprintf(&basedir, "%s", ((struct route_info *)tree->route)->path);
		if (ret<0)
			return -1;

		ret = basename(basedir) ? 0 : -1;
		if (ret<0)
			goto out_free_basedir;

		ret = asprintf(&newpath, "%s/%s", basedir, direntp->d_name);
		if (ret<0)
			goto out_free_basedir;

		ret = stat(newpath, &s);
		if (ret)
			goto out_free_newpath;

		if (S_ISDIR(s.st_mode)) {

			ret = -1;

			ri = malloc(sizeof(*ri));
			ri->path = strdup(newpath);
			child = tree_alloc(ri, tree->depth+1);
			if (!child)
				goto out_free_newpath;

			tree_add_child(tree, child);

			tree->nrchild++;
			ret = clock_dir_scan(child);
		}

		out_free_newpath:
			free(newpath);
		out_free_basedir:
			free(basedir);

		if (ret) break;
	}

	closedir(dir);
	return 0;
}

struct clock_info *clock_alloc(void)
{
	struct clock_info *ci;

	ci = malloc(sizeof(*ci));
	if (ci)
		memset(ci, 0, sizeof(*ci));

	return ci;
}

int read_clock_cb(struct tree *t, void *data)
{
	struct clock_info *ci = t->private;

	file_read_value(((struct route_info *)t->route)->path, "clk_rate",
		"%u", &ci->rate);

	log_inf("read %s/%s, %u Hz\n",
		((struct route_info *)t->route)->path, "clk_rate", ci->rate);

	log_inf("expanded %s\n", ci->expanded==true?"true":"false");

	return 0;
}

int fill_clock_cb(struct tree *t, void *data)
{
	struct clock_info *ci;

	ci = clock_alloc();
	if (!ci)
		return -1;

	t->private = ci;

	/*skip the root node */
	if (!t->parent) {
		ci->expanded = true;
		return 0;
	}

	return read_clock_cb(t, data);

}

int fill_clock_tree(void)
{
	return tree_for_each(clock_tree, fill_clock_cb, NULL);
}
