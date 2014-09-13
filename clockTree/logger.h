
#ifndef __logger_h__
#define __logger_h__

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

#endif
