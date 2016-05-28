#ifndef __F__MYPRS_UDIZHUWITHMEPLEASE__DOUDIZHUWITHMEPLEASE_MINMAXTREE_H__
#define __F__MYPRS_UDIZHUWITHMEPLEASE__DOUDIZHUWITHMEPLEASE_MINMAXTREE_H__

#include <iostream>

#define GAME_MSG_DEFAULT( x ) std::cout<<x;
#define GAME_MSG_SYS( x ) std::cout<<"   ( "<<x<<" ) "<<std::endl
#define GAME_MSG_INFO_ENDL( x ) std::cout<<" --- "<<x<<" --- "<<std::endl
#define GAME_MSG_INFO_NOENDL( x ) std::cout<<" --- "<<x<<" --- "
#define GAME_MSG_SEP_LINE() std::cout<<"------------------------"<<std::endl
#define GAME_MSG_SEP_ENDL() std::cout<<std::endl;

#if 0

#define DEBUG_TRACE_FUNC( x ) std::cout<<" Debug(Trace func): ("<<this<<")"<<(x)<<std::endl
#define DEBUG_LOG( x ) std::cout<<" Log: ("<<this<<")"<<(x)<<std::endl

#else

#define DEBUG_TRACE_FUNC( x ) (x)
#define DEBUG_LOG( x ) (x)

#endif

#endif