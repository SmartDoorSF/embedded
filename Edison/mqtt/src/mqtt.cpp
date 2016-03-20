#include "mraa.hpp"
#include <iostream>
using namespace std;

int main() {
  /* Setup your example here, code that should run once
   */

  mraa::Platform platform = mraa::getPlatformType();
  mraa::Gpio* d_pin = NULL;
  switch (platform) {
  	  case mraa::INTEL_EDISON_FAB_C:
  		  d_pin = new mraa::Gpio(13, true, false);
  		  break;
  	  default:
  		  std::cerr << "Unsupported platform, exiting" << std::endl;
  	  	  return mraa::ERROR_INVALID_PLATFORM;
  }

  if (d_pin == NULL) {
	  std::cerr <<"Can't create mraa::Gpio object, exiting" << std::endl;
	  return mraa::ERROR_UNSPECIFIED;
  }

  // set the pin as output
  if (d_pin->dir(mraa::DIR_OUT) != mraa::SUCCESS) {
	  std::cerr << "Can't set digital pin as output, exiting" << std::endl;
	  return MRAA_ERROR_UNSPECIFIED;
  }

  /* Code in this loop will run repeatedly
   */
  for (;;) {
	  d_pin -> write(1);
	  sleep(1);
	  d_pin -> write(0);
	  sleep(1);
  }

  return mraa::SUCCESS;
}
