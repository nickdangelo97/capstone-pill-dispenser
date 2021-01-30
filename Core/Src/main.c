#include "main.h"

#include "cmsis_os.h"

#include <touchgfx/hal/BoardConfiguration.hpp>


osThreadId_t TouchGFXTaskHandle;
const osThreadAttr_t TouchGFXTask_attributes = {
  .name = "TouchGFXTask",
  .priority = (osPriority_t)osPriorityNormal,
  .stack_size = 4096 * 4
};

void TouchGFX_Task(void* argument);

int main(void)
{
	/*Hardware and GFX init*/
	hw_init();
	MX_TouchGFX_Init();

	osKernelInitialize();

	TouchGFXTaskHandle = osThreadNew(TouchGFX_Task, NULL, &TouchGFXTask_attributes);

	osKernelStart();

	while (1)
	{
	}
}


/* Remnants of original main file; forward decleration seems to work */
// __weak void TouchGFX_Task(void* argument)
// {
//     /* USER CODE BEGIN 5 */
//     for (;;)
//     {
//         osDelay(1);
//     }
//     /* USER CODE END 5 */
// }


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	   tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	   /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */