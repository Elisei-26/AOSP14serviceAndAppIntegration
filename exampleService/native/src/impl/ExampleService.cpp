#include "ExampleService.hpp"
#include <utils/Log.h>
#include <fstream>
#include <numeric>

#ifdef LOG_TAG
   #undef LOG_TAG
#endif
#define LOG_TAG "example_service"

namespace example {
   namespace service {

      ::std::shared_ptr<ExampleService> ExampleService::s_instance = NULL;

      ::std::shared_ptr<ExampleService> ExampleService::GetInstance() {
         if (s_instance == NULL) {
            s_instance = ndk::SharedRefBase::make<ExampleService>();
         }
         return s_instance;
      }

      ExampleService::ExampleService() {
         short line_index = 0;
         ReadColumnFromCSV(line_index, cpu_column_data);
         line_index = 1;
         ReadColumnFromCSV(line_index, gpu_column_data);
         line_index = 2;
         ReadColumnFromCSV(line_index, ambient_column_data);
      }
      ExampleService::~ExampleService() {}

      ::ndk::ScopedAStatus ExampleService::GetValues(esapinamespace::ExampleType* _aidl_return) {
         ::aidl::example::service::api::ExampleType extype;
         
         std::vector<int32_t> cert(10);
         for (int32_t i : cert) {
            cert.push_back(i);
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

      void ExampleService::ReadColumnFromCSV(int col_index, std::vector<float>& column_data) {
         std::ifstream file("/vendor/etc/temperatures.csv");

         if (!file.is_open()) {
            std::cerr << "Unable to open file: " << "/vendor/etc/temperatures.csv" << std::endl;
            return;
         }

         std::string line;
         while (getline(file, line)) {
               std::stringstream ss(line);
               std::string cell;
               int currentCol = 0;
               while (getline(ss, cell, ' ') && currentCol <= col_index) {
                  if (currentCol == col_index) {
                     column_data.push_back(std::stof(cell));
                     break; // Stop reading after finding the desired column
                  }
                  ++currentCol;
               }
         }
         file.close();
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
         float max = *max_element(vec.begin(), vec.end());
         return max;
      }

      float ExampleService::CalculateAverageValue(const std::vector<float>& vec) {
         float sum = reduce(vec.begin(), vec.end(), 0);
         return ( sum / vec.size());
      }

      float ExampleService::CpuValue() {
         cpu_temp = GetCpuNextValue(cpu_column_data);
         return cpu_temp;
      }

      float ExampleService::GpuValue() {
         gpu_temp = GetGpuNextValue(gpu_column_data);
         return gpu_temp;
      }

      float ExampleService::AmbientValue() {
         ambient_temp = GetAmbientNextValue(ambient_column_data);
         return ambient_temp;
      }

      float ExampleService::MaxCpuValue() {
         cpu_temp = CalculateMaxValue(cpu_column_data);
         return cpu_temp;
      }

      float ExampleService::MaxGpuValue() {
         gpu_temp = CalculateMaxValue(gpu_column_data);
         return gpu_temp;
      }

      float ExampleService::MaxAmbientValue() {
         ambient_temp = CalculateMaxValue(ambient_column_data);
         return ambient_temp;
      }

      float ExampleService::AverageCpuValue() {
         cpu_temp = CalculateAverageValue(cpu_column_data);
         return cpu_temp;
      }

      float ExampleService::AverageGpuValue() {
         gpu_temp = CalculateAverageValue(gpu_column_data);
         return gpu_temp;
      }

      float ExampleService::AverageAmbientValue() {
         ambient_temp = CalculateAverageValue(ambient_column_data);
         return ambient_temp;
      }
   }
}