
//开关文件

//1.模式开关决定7670输出模式

//#define Model_YUV   //模式选择	YUV模式默认去除UV

//#define BaclcWhiteOutput //黑白输出开关

//2.数据去向开关

//#define PC_OutPut    //送给串口
//#define NoneOutput   //单片机自己处理

//数据线个数
#define DataOnly  //只有一根











/*
正常八位数据线推荐模式--怕自己会忘记
#define Model_RGB    //正常输出RGB +QVGB 
#define TFT_OutPut   //数据给TFT

串口数据输出模式
#define Model_YUV   //模式选择	YUV模式默认去除UV
#define Mode_QICF   //分辨率选择 QICF 减少数据量
#define PC_OutPut    //送给串口
#define DataOnly  //只有一根
*/

