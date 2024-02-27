package example.service.api;

@VintfStability
interface IExampleService {
    example.service.api.ExampleType getValues ();
    float getCpuTemperature();
    float getGpuTemperature();
    float getAmbientTemperature();
    float getAverageCpuTemperature();
    float getAverageGpuTemperature();
    float getAverageAmbientTemperature();
    float getMaxCpuTemperature();
    float getMaxGpuTemperature();
    float getMaxAmbientTemperature();
}