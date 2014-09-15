
#ifndef __config_h__
#define __config_h__

#define __DEBUG__

#define _red		"\033[31m"
#define _blue		"\033[34m"
#define _default	"\033[0m"

#ifdef __DEBUG__
#define log_err(fmt, arg...) printf(_red "[err]: "_default fmt, ##arg)
#define log_inf(fmt, arg...) printf(_blue"[inf]: "_default fmt, ##arg)
#else
#define log_err(fmt, ...) 
#define log_inf(fmt, ...) 
#endif



#define MAX_NAME_LEN		(64)
#define MAX_BOOK_NAME_LEN	(128)

#endif
