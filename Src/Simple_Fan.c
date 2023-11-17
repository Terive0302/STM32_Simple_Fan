/*
 * Simple_Fan.c
 *
 *  Created on: Sep 26, 2023
 *      Author: user
 */

#include "I2C_LCD.h"

void clear_lcd_buff(void)
{
  char buff[16];

  for (int i = 0; i < sizeof(buff); i++)
  {
    buff[i] = ' ';
  }
  print_zero_row(buff);
  print_one_row(buff);
}

void print_zero_row(char *str)
{
  lcd_put_cur(0, 0);
  lcd_send_string(str);
  HAL_Delay(50);
}

void print_one_row(char *str)
{
  lcd_put_cur(1, 0);
  lcd_send_string(str);
  HAL_Delay(50);
}

void power(state)
{
  switch (state)
  {
    case 0:
      clear_lcd_buff();
      TIM3->CCR1 = 0;
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, RESET);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, RESET);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, RESET);
      HAL_Delay(10);
      print_zero_row("Fan Stop");
      print_one_row("LED ALL OFF ");
      break;

    case 1:
      clear_lcd_buff();
      TIM3->CCR1 = 450;
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, SET);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, RESET);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, RESET);
      HAL_Delay(10);
      print_zero_row("Fan Power : 1");
      print_one_row("LED ON RED");
      break;

    case 2:
      clear_lcd_buff();
      TIM3->CCR1 = 550;
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, SET);
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, RESET);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, RESET);
      HAL_Delay(10);
      print_zero_row("Fan Power : 2");
      print_one_row("LED ON GREEN   ");
      break;

    case 3:
      clear_lcd_buff();
      TIM3->CCR1 = 700;
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, SET);
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, RESET);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, RESET);
      HAL_Delay(10);
      print_zero_row("Fan Power : 3");
      print_one_row("LED ON WHITE   ");
      break;

    default:
      break;
  }
}
