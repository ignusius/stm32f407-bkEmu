#ifndef _ETL_STM32F4XX_FLASH_H_INCLUDED
#define _ETL_STM32F4XX_FLASH_H_INCLUDED

#include <etl/STM32F4xx/types.h>

namespace etl {
namespace stm32f4xx {

struct Flash {
  #define ETL_BFF_DEFINITION_FILE "etl/STM32F4xx/flash.reg"
  #include "etl/biffield/generate.h"
  #undef ETL_BFF_DEFINITION_FILE
};

extern Flash flash;

}  // namespace stm32f4xx
}  // namespace etl

#endif  // _ETL_STM32F4XX_FLASH_H_INCLUDED
