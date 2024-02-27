#ifndef EXAMPLE_SERVICE
#define EXAMPLE_SERVICE

#include <aidl/example/service/api/BnExampleService.h>

namespace esapinamespace = ::aidl::example::service::api;

namespace example {
   namespace service {
      class ExampleService : public ::aidl::example::service::api::BnExampleService {
         private:
            static ::std::shared_ptr<ExampleService> S_INSTANCE;
            void readColumnFromCSV(int colIndex, std::vector<float>& columnData);
            float getCpuNextValue(std::vector<float>& vec);
            float getGpuNextValue(std::vector<float>& vec);
            float getAmbientNextValue(std::vector<float>& vec);
            float calculateMaxValue(const std::vector<float>& vec);
            float calculateAverageValue(const std::vector<float>& vec);

            float cpuValue();
            float gpuValue();
            float ambientValue();
            float maxCpuValue();
            float maxGpuValue();
            float maxAmbientValue();
            float averageCpuValue();
            float averageGpuValue();
            float averageAmbientValue();

            ::std::vector<float> cpuColumnData, gpuColumnData, ambientColumnData;
            float cpuTemp, gpuTemp, ambientTemp;
            
         public:
            ExampleService();
            ~ExampleService();

            static ::std::shared_ptr<ExampleService> getInstance();

            // IExampleService AIDL interface callbacks
            virtual ::ndk::ScopedAStatus getValues(esapinamespace::ExampleType* _aidl_return) final;
            virtual ::ndk::ScopedAStatus getCpuTemperature(float* _aidl_return) final;
            virtual ::ndk::ScopedAStatus getGpuTemperature(float* _aidl_return) final;
            virtual ::ndk::ScopedAStatus getAmbientTemperature(float* _aidl_return) final;
            virtual ::ndk::ScopedAStatus getAverageCpuTemperature(float* _aidl_return) final;
            virtual ::ndk::ScopedAStatus getAverageGpuTemperature(float* _aidl_return) final;
            virtual ::ndk::ScopedAStatus getAverageAmbientTemperature(float* _aidl_return) final;
            virtual ::ndk::ScopedAStatus getMaxCpuTemperature(float* _aidl_return) final;
            virtual ::ndk::ScopedAStatus getMaxGpuTemperature(float* _aidl_return) final;
            virtual ::ndk::ScopedAStatus getMaxAmbientTemperature(float* _aidl_return) final;

            const std::string getServiceName(void) {
               return std::string() + descriptor + "/default";
            }
      };
   }
}
#endif  // EXAMPLE_SERVICE