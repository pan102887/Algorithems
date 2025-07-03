#ifndef COMMON_H
#define COMMON_H

#ifdef __cplusplus
extern "C" {

#define IF_CPP_THEN(content) content

}
#else
#define IF_CPP_THEN(content)
#endif // __cplusplus


#endif // COMMON_H