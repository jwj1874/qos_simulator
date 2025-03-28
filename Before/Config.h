#ifndef CONFIG_H
#define CONFIG_H

#define SIM_DURATION 1000                //전체 시뮬레이션 시간
#define SENSOR_COUNT 80                 //센서 수
#define SENSOR_TX_INTERVAL 3             //센서 전송 주기


#define ENABLE_PREDICTION 1             //예측 기반 전송 생략 사용 여부 (0 / 1)
#define PREDICTION_ERROR_THRESHOLD 0.5  //예측 오차 임계값
#define BASE_SUCCESS_RATE 0.95          //전송 성공률
#endif