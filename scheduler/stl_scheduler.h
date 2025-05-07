#if __STL__


#include "stl.h"

#include "stl_al_os.h"
#include "stl_tssp.h"
#include "stl_core.h"


#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/


void STL_schedule_runtime(STL_CPUS cpu,STL_ERROR_T *err);
void STL_schedule_bootime(STL_CPUS cpu,STL_ERROR_T *err);


#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*__STL__*/