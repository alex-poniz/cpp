#include <cstdint>
#include <iostream>
#include <iomanip>

double decode(int snr)
{
  double ret = 0;
  const int16_t snr_16 = (int16_t)snr;

  int16_t exponent = (snr_16 & 0b1111000000000000) >> 12;
  int16_t mantissa =  snr_16 & 0b0000011111111111;
  int16_t sign     = (snr_16 & 0b0000100000000000) >> 11;

  if (exponent) {
    int16_t basis = mantissa | (sign ? 0b0001000000000000 : 0b0000100000000000);
    ret = (double)basis / (1 << (25 - exponent)); 

    if (sign)
  	ret = -ret;
  }
  else {
    int16_t basis = mantissa;
    
    if (sign)
      basis = -(~(mantissa - 1) & 0b0000011111111111);
    
    ret = (double)basis / (1 << 24);
  }
    
  return ret;
}

int main() 
{
  int input[5] = {0x000, 0x0020, 0x10ff, 0x0900, 0xf800};

  for (int i = 0; i < 5; i++) {	
    std::cout << "Input: " << std::showbase << std::setw(6) << std::hex << input[i] 
      << std::fixed << std::setprecision(20) << " Result: " << (double)decode(input[i]) 
      << std::endl;
  }

  return 0;
}

