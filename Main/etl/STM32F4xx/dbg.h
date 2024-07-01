#ifndef _ETL_STM32F4XX_DBG_H_INCLUDED
#define _ETL_STM32F4XX_DBG_H_INCLUDED

#include <etl/STM32F4xx/types.h>

namespace etl {
namespace stm32f4xx {

struct Dbg {
  #define ETL_BFF_DEFINITION_FILE "etl/STM32F4xx/dbg.reg"
  #include "etl/biffield/generate.h"
  #undef ETL_BFF_DEFINITION_FILE
};

extern Dbg dbg;

}  // namespace stm32f4xx
}  // namespace etl

#endif  // _ETL_STM32F4XX_DBG_H_INCLUDED
