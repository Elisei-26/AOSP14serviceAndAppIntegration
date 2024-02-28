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

      ::std::shared_ptr<ExampleService> ExampleService::GetInstance() {
         if (S_INSTANCE == NULL) {
            S_INSTANCE = ndk::SharedRefBase::make<ExampleService>();
         }
         return S_INSTANCE;
      }

      ExampleService::ExampleService() {
         ReadColumnFromCSV(0, cpuColumnData);
         ReadColumnFromCSV(1, gpuColumnData);
         ReadColumnFromCSV(2, ambientColumnData);
      }
      ExampleService::~ExampleService() {}

      ::ndk::ScopedAStatus ExampleService::GetValues(esapinamespace::ExampleType* _aidl_return) {
         ::aidl::example::service::api::ExampleType extype;
         
         std::vector<int32_t> cert(10);
         // for (const auto& i : cert) {
         //    cert.push(i.index + 1);
         // }
         for (unsigned int i = 0; i < cert.size(); ++i) {
            cert[i] = i;
         }

         extype.cert = cert;
         extype.retval = (int64_t) 2;

         *_aidl_return = extype;
         return ndk::ScopedAStatus::ok();
      }


      ::ndk::ScopedAStatus ExampleService::GetCpuTemperature(float* _aidl_return) {
         *_aidl_return = CpuValue();
         return ndk::ScopedAStatus::ok();
      }

      ::ndk::ScopedAStatus ExampleService::GetGpuTemperature(float* _aidl_return) {
         *_aidl_return = CpuValue();
         return ndk::ScopedAStatus::ok();
      }

      ::ndk::ScopedAStatus ExampleService::GetAmbientTemperature(float* _aidl_return) {
         *_aidl_return = AmbientValue();
         return ndk::ScopedAStatus::ok();
      }

      ::ndk::ScopedAStatus ExampleService::GetAverageCpuTemperature(float* _aidl_return) {
         *_aidl_return = AverageCpuValue();
         return ndk::ScopedAStatus::ok();
      }

      ::ndk::ScopedAStatus ExampleService::GetAverageGpuTemperature(float* _aidl_return) {
         *_aidl_return = AverageGpuValue();
         return ndk::ScopedAStatus::ok();
      }

      ::ndk::ScopedAStatus ExampleService::GetAverageAmbientTemperature(float* _aidl_return) {
         *_aidl_return = AverageAmbientValue();
         return ndk::ScopedAStatus::ok();
      }

      ::ndk::ScopedAStatus ExampleService::GetMaxCpuTemperature(float* _aidl_return) {
         *_aidl_return = MaxCpuValue();
         return ndk::ScopedAStatus::ok();
      }

      ::ndk::ScopedAStatus ExampleService::GetMaxGpuTemperature(float* _aidl_return) {
         *_aidl_return = MaxGpuValue();
         return ndk::ScopedAStatus::ok();
      }

      ::ndk::ScopedAStatus ExampleService::GetMaxAmbientTemperature(float* _aidl_return) {
         *_aidl_return = MaxAmbientValue();
         return ndk::ScopedAStatus::ok();
      }

      void ExampleService::ReadColumnFromCSV(int colIndex, std::vector<float>& columnData) {
         std::ifstream file("/vendor/etc/temperatures.csv");
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

      float ExampleService::GetCpuNextValue(std::vector<float>& vec) {
         static std::size_t index_cpu = 0;
         if (index_cpu >= vec.size()) {
            index_cpu = 0;
         }
         return vec[index_cpu++];
      }

      float ExampleService::GetGpuNextValue(std::vector<float>& vec) {
         static std::size_t index_gpu = 0;
         if (index_gpu >= vec.size()) {
            index_gpu = 0;
         }
         return vec[index_gpu++];
      }

      float ExampleService::GetAmbientNextValue(std::vector<float>& vec) {
         static std::size_t index_ambient = 0;
         if (index_ambient >= vec.size()) {
            index_ambient = 0;
         }
         return vec[index_ambient++];
      }

      float ExampleService::CalculateMaxValue(const std::vector<float>& vec) {
         float max = vec[0]; // Initialize max to the first element of the vector
         // Iterate through the vector to find the maximum element
         // for (const auto& i.index = 1 : vec) {
         //    if (i > max) {
         //          max = i;
         //    }
         // }

         for (size_t i = 1; i < vec.size(); ++i) {
            if (vec[i] > max) {
                  max = vec[i];
            }
         }
         return max;
      }

      float ExampleService::CalculateAverageValue(const std::vector<float>& vec) {
         float sum = 0.0;
         // for (const auto& i : vec) {
         //    sum += i;
         // }
         for (int i = 0; i < (int)vec.size(); ++i) {
            sum += vec[i];
         }
         return ( sum / vec.size());
      }

      float ExampleService::CpuValue() {
         cpuTemp = GetCpuNextValue(cpuColumnData);
         return cpuTemp;
      }

      float ExampleService::GpuValue() {
         gpuTemp = GetGpuNextValue(gpuColumnData);
         return gpuTemp;
      }

      float ExampleService::AmbientValue() {
         ambientTemp = GetAmbientNextValue(ambientColumnData);
         return ambientTemp;
      }

      float ExampleService::MaxCpuValue() {
         cpuTemp = CalculateMaxValue(cpuColumnData);
         return cpuTemp;
      }

      float ExampleService::MaxGpuValue() {
         gpuTemp = CalculateMaxValue(gpuColumnData);
         return gpuTemp;
      }

      float ExampleService::MaxAmbientValue() {
         ambientTemp = CalculateMaxValue(ambientColumnData);
         return ambientTemp;
      }

      float ExampleService::AverageCpuValue() {
         cpuTemp = CalculateAverageValue(cpuColumnData);
         return cpuTemp;
      }

      float ExampleService::AverageGpuValue() {
         gpuTemp = CalculateAverageValue(gpuColumnData);
         return gpuTemp;
      }

      float ExampleService::AverageAmbientValue() {
         ambientTemp = CalculateAverageValue(ambientColumnData);
         return ambientTemp;
      }
   }
}