#include "ExampleService.hpp"
#include <utils/Log.h>
#include <fstream>

#ifdef LOG_TAG
   #undef LOG_TAG
#endif
#define LOG_TAG "example_service"

namespace example {
   namespace service {

      ::std::shared_ptr<ExampleService> ExampleService::S_INSTANCE = NULL;

      ::std::shared_ptr<ExampleService> ExampleService::getInstance() {
         if (S_INSTANCE == NULL) {
            S_INSTANCE = ndk::SharedRefBase::make<ExampleService>();
         }
         return S_INSTANCE;
      }

      ExampleService::ExampleService() {
         readColumnFromCSV(0, cpuColumnData);
         readColumnFromCSV(1, gpuColumnData);
         readColumnFromCSV(2, ambientColumnData);
      }
      ExampleService::~ExampleService() {}

      ::ndk::ScopedAStatus ExampleService::getValues(esapinamespace::ExampleType* _aidl_return) {
         ::aidl::example::service::api::ExampleType extype;
         
         std::vector<int32_t> cert(10);
         for (unsigned int i = 0; i < cert.size(); ++i) {
            cert[i] = i;
         }

         extype.cert = cert;
         extype.retval = (int64_t) 2;

         *_aidl_return = extype;
         return ndk::ScopedAStatus::ok();
      }


      ::ndk::ScopedAStatus ExampleService::getCpuTemperature(float* _aidl_return) {
         *_aidl_return = cpuValue();
         return ndk::ScopedAStatus::ok();
      }

      ::ndk::ScopedAStatus ExampleService::getGpuTemperature(float* _aidl_return) {
         *_aidl_return = gpuValue();
         return ndk::ScopedAStatus::ok();
      }

      ::ndk::ScopedAStatus ExampleService::getAmbientTemperature(float* _aidl_return) {
         *_aidl_return = ambientValue();
         return ndk::ScopedAStatus::ok();
      }

      ::ndk::ScopedAStatus ExampleService::getAverageCpuTemperature(float* _aidl_return) {
         *_aidl_return = averageCpuValue();
         return ndk::ScopedAStatus::ok();
      }

      ::ndk::ScopedAStatus ExampleService::getAverageGpuTemperature(float* _aidl_return) {
         *_aidl_return = averageGpuValue();
         return ndk::ScopedAStatus::ok();
      }

      ::ndk::ScopedAStatus ExampleService::getAverageAmbientTemperature(float* _aidl_return) {
         *_aidl_return = averageAmbientValue();
         return ndk::ScopedAStatus::ok();
      }

      ::ndk::ScopedAStatus ExampleService::getMaxCpuTemperature(float* _aidl_return) {
         *_aidl_return = maxCpuValue();
         return ndk::ScopedAStatus::ok();
      }

      ::ndk::ScopedAStatus ExampleService::getMaxGpuTemperature(float* _aidl_return) {
         *_aidl_return = maxGpuValue();
         return ndk::ScopedAStatus::ok();
      }

      ::ndk::ScopedAStatus ExampleService::getMaxAmbientTemperature(float* _aidl_return) {
         *_aidl_return = maxAmbientValue();
         return ndk::ScopedAStatus::ok();
      }

      void ExampleService::readColumnFromCSV(int colIndex, std::vector<float>& columnData) {
         std::ifstream file;
         file.open("/vendor/etc/temperatures.csv");
         std::string line;

         if (file.is_open()) {
            while (getline(file, line)) {
                  std::stringstream ss(line);
                  std::string cell;
                  int currentCol = 0;
                  while (getline(ss, cell, ' ') && currentCol <= colIndex) {
                     if (currentCol == colIndex) {
                        columnData.push_back(std::stof(cell));
                        break; // Stop reading after finding the desired column
                     }
                     ++currentCol;
                  }
            }
            file.close();
         } else {
            std::cerr << "Unable to open file: " << "/vendor/etc/temperatures.csv" << std::endl;
         }
      }

      float ExampleService::getCpuNextValue(std::vector<float>& vec) {
         static std::size_t index_cpu = 0;
         if (index_cpu >= vec.size()) {
            index_cpu = 0;
         }
         return vec[index_cpu++];
      }

      float ExampleService::getGpuNextValue(std::vector<float>& vec) {
         static std::size_t index_gpu = 0;
         if (index_gpu >= vec.size()) {
            index_gpu = 0;
         }
         return vec[index_gpu++];
      }

      float ExampleService::getAmbientNextValue(std::vector<float>& vec) {
         static std::size_t index_ambient = 0;
         if (index_ambient >= vec.size()) {
            index_ambient = 0;
         }
         return vec[index_ambient++];
      }

      float ExampleService::calculateMaxValue(const std::vector<float>& vec) {
         float max = vec[0]; // Initialize max to the first element of the vector
         // Iterate through the vector to find the maximum element
         for (size_t i = 1; i < vec.size(); ++i) {
            if (vec[i] > max) {
                  max = vec[i];
            }
         }
         return max;
      }

      float ExampleService::calculateAverageValue(const std::vector<float>& vec) {
         float sum = 0.0;
         for ( int i = 0; i < (int)vec.size(); ++i) {
            sum += vec[i];
         }
         return ( sum / vec.size());
      }

      float ExampleService::cpuValue() {
         cpuTemp = getCpuNextValue(cpuColumnData);
         return cpuTemp;
      }

      float ExampleService::gpuValue() {
         gpuTemp = getGpuNextValue(gpuColumnData);
         return gpuTemp;
      }

      float ExampleService::ambientValue() {
         ambientTemp = getAmbientNextValue(ambientColumnData);
         return ambientTemp;
      }

      float ExampleService::maxCpuValue() {
         cpuTemp = calculateMaxValue(cpuColumnData);
         return cpuTemp;
      }

      float ExampleService::maxGpuValue() {
         gpuTemp = calculateMaxValue(gpuColumnData);
         return gpuTemp;
      }

      float ExampleService::maxAmbientValue() {
         ambientTemp = calculateMaxValue(ambientColumnData);
         return ambientTemp;
      }

      float ExampleService::averageCpuValue() {
         cpuTemp = calculateAverageValue(cpuColumnData);
         return cpuTemp;
      }

      float ExampleService::averageGpuValue() {
         gpuTemp = calculateAverageValue(gpuColumnData);
         return gpuTemp;
      }

      float ExampleService::averageAmbientValue() {
         ambientTemp = calculateAverageValue(ambientColumnData);
         return ambientTemp;
      }
   }
}