
#define _GNU_SOURCE
#include <stdio.h>
#undef _GNU_SOURCE

#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "logger.h"
#include "tree.h"

#ifdef __DEBUG__
#define _clk_dir "/home/shmily/bogon/clockTree/clk"
#else
#define _clk_dir "/sys/kernel/debug/clk"
#endif

struct clock_data {
	char *path;
	char *name;
};

struct tree *clock;

int clock_scan(struct tree *tree);

int main(void)
{
	struct clock_data *cd;

	cd = malloc(sizeof(*cd));
	if (!cd) {
		log_err("clock_data, malloc faild\n");
		return -1;
	}

	cd->path = _clk_dir;
	clock = tree_alloc(cd, 0);
	if (!clock)
		return -1;

	clock_scan(clock);

	return 0;
}

int clock_scan(struct tree *tree)
{
	int ret;
	DIR *dir;
	char *basedir, *newpath;
	struct stat s;
	struct dirent dirent, *direntp;

	log_inf("try to scan directory %s\n", ((struct clock_data *)tree->data)->path);
	dir = opendir(((struct clock_data *)tree->data)->path);
	if (!dir) {
		log_err("unable to open directory %s\n",
			((struct clock_data *)tree->data)->path);
		return -1;
	}

	while (!readdir_r(dir, &dirent, &direntp)) {
		struct tree *child;
		struct clock_data *cd;

		if (!direntp) break;
		if (direntp->d_name[0]=='.') continue;

		ret = asprintf(&basedir, "%s", ((struct clock_data *)tree->data)->path);
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

			cd = malloc(sizeof(*cd));
			cd->path = strdup(newpath);
			child = tree_alloc(cd, tree->depth+1);
			if (!child)
				goto out_free_newpath;

			tree_add_child(tree, child);

			tree->nrchild++;
			ret = clock_scan(child);
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
