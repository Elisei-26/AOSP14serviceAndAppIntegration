package example.service.api;

@VintfStability
interface IExampleService {
    example.service.api.ExampleType GetValues ();
    float GetCpuTemperature();
    float GetGpuTemperature();
    float GetAmbientTemperature();
    float GetAverageCpuTemperature();
    float GetAverageGpuTemperature();
    float GetAverageAmbientTemperature();
    float GetMaxCpuTemperature();
    float GetMaxGpuTemperature();
    float GetMaxAmbientTemperature();
}