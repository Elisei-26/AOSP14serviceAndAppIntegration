package example.service.manager;

import android.util.Log;
import android.os.ServiceManager;
import android.os.IBinder;
import android.os.RemoteException;

import example.service.api.IExampleService;

public class ExampleServiceManager {
    private IBinder binder;
    private IExampleService service;

    private static ExampleServiceManager instance;

    private ExampleServiceManager() {
        binder = ServiceManager.getService("example.service.api.IExampleService/default");
        if (binder != null) {
            service = IExampleService.Stub.asInterface(binder);

            if (service != null) {
                Log.d("ExampleServiceManager", "Service accessed succesfully!");
            } else {
                Log.e("ExampleServiceManager", "Error to access service ExampleServiceManager!");
            }
            
        } else {
            Log.e("ExampleServiceManager", "Error to access binder!");
        }
    }

    public static ExampleServiceManager GetInstance() {
        if (instance == null) {
            instance = new ExampleServiceManager();
        }
        return instance;
    }

    public Float GetCpuTemperature() throws RemoteException {
        Log.i("ExampleServiceManager", "W - GetCpuTemperature");
        return service.GetCpuTemperature();
    }

    public Float GetGpuTemperature() throws RemoteException {
        Log.i("ExampleServiceManager", "W - GetGpuTemperature");
        return service.GetGpuTemperature();
    }

    public Float GetAmbientTemperature() throws RemoteException {
        Log.i("ExampleServiceManager", "W - GetAmbientTemperature");
        return service.GetAmbientTemperature();
    }

    public Float GetAverageCpuTemperature() throws RemoteException {
        Log.i("ExampleServiceManager", "W - GetAverageCpuTemperature");
        return service.GetAverageCpuTemperature();
    }

    public Float GetAverageGpuTemperature() throws RemoteException {
        Log.i("ExampleServiceManager", "W - GetAverageGpuTemperature");
        return service.GetAverageGpuTemperature();
    }

    public Float GetAverageAmbientTemperature() throws RemoteException {
        Log.i("ExampleServiceManager", "W - GetAverageAmbientTemperature");
        return service.GetAverageAmbientTemperature();
    }

    public Float GetMaxCpuTemperature() throws RemoteException {
        Log.i("ExampleServiceManager", "W - GetMaxCpuTemperature");
        return service.GetMaxCpuTemperature();
    }

    public Float GetMaxGpuTemperature() throws RemoteException {
        Log.i("ExampleServiceManager", "W - GetMaxGpuTemperature");
        return service.GetMaxGpuTemperature();
    }

    public Float GetMaxAmbientTemperature() throws RemoteException {
        Log.i("ExampleServiceManager", "W - GetMaxAmbientTemperature");
        return service.GetMaxAmbientTemperature();
    }
}