#ifndef EXAMPLE_SERVICE
#define EXAMPLE_SERVICE

#include <aidl/example/service/api/BnExampleService.h>

namespace esapinamespace = ::aidl::example::service::api;

namespace example {
   namespace service {
      class ExampleService : public ::aidl::example::service::api::BnExampleService {
         private:
            static ::std::shared_ptr<ExampleService> s_instance;
            void ReadColumnFromCSV(int col_index, std::vector<float>& column_data);
            float GetCpuNextValue(std::vector<float>& vec);
            float GetGpuNextValue(std::vector<float>& vec);
            float GetAmbientNextValue(std::vector<float>& vec);
            float CalculateMaxValue(const std::vector<float>& vec);
            float CalculateAverageValue(const std::vector<float>& vec);

            float CpuValue();
            float GpuValue();
            float AmbientValue();
            float MaxCpuValue();
            float MaxGpuValue();
            float MaxAmbientValue();
            float AverageCpuValue();
            float AverageGpuValue();
            float AverageAmbientValue();

            ::std::vector<float> cpu_column_data, gpu_column_data, ambient_column_data;
            float cpu_temp, gpu_temp, ambient_temp;

         public:
            ExampleService();
            ~ExampleService();

            static ::std::shared_ptr<ExampleService> GetInstance();

            // IExampleService AIDL interface callbacks
            virtual ::ndk::ScopedAStatus GetValues(esapinamespace::ExampleType* _aidl_return) final;
            virtual ::ndk::ScopedAStatus GetCpuTemperature(float* _aidl_return) final;
            virtual ::ndk::ScopedAStatus GetGpuTemperature(float* _aidl_return) final;
            virtual ::ndk::ScopedAStatus GetAmbientTemperature(float* _aidl_return) final;
            virtual ::ndk::ScopedAStatus GetAverageCpuTemperature(float* _aidl_return) final;
            virtual ::ndk::ScopedAStatus GetAverageGpuTemperature(float* _aidl_return) final;
            virtual ::ndk::ScopedAStatus GetAverageAmbientTemperature(float* _aidl_return) final;
            virtual ::ndk::ScopedAStatus GetMaxCpuTemperature(float* _aidl_return) final;
            virtual ::ndk::ScopedAStatus GetMaxGpuTemperature(float* _aidl_return) final;
            virtual ::ndk::ScopedAStatus GetMaxAmbientTemperature(float* _aidl_return) final;

            const std::string GetServiceName(void) {
               return std::string() + descriptor + "/default";
            }
      };
   }
}
#endif  // EXAMPLE_SERVICE