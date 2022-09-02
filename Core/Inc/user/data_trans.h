//
// Created by hhc on 2022/4/26.
//

#ifndef MAKEROBOT_DATA_TRANS_H
#define MAKEROBOT_DATA_TRANS_H

#include "usart.h"
void start_data();
void send_data(uint8_t *data, uint8_t len);

void USER_UART_IDLECallback(UART_HandleTypeDef *huart);

#endif //MAKEROBOT_DATA_TRANS_H
