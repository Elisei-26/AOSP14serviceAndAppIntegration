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

    public static ExampleServiceManager getInstance() {
        if (instance == null) {
            instance = new ExampleServiceManager();
        }
        return instance;
    }

    public Float getCpuTemperature() throws RemoteException {
        Log.i("ExampleServiceManager", "W - getCpuTemperature");
        return service.getCpuTemperature();
    }

    public Float getGpuTemperature() throws RemoteException {
        Log.i("ExampleServiceManager", "W - getGpuTemperature");
        return service.getGpuTemperature();
    }

    public Float getAmbientTemperature() throws RemoteException {
        Log.i("ExampleServiceManager", "W - getAmbientTemperature");
        return service.getAmbientTemperature();
    }

    public Float getAverageCpuTemperature() throws RemoteException {
        Log.i("ExampleServiceManager", "W - getAverageCpuTemperature");
        return service.getAverageCpuTemperature();
    }

    public Float getAverageGpuTemperature() throws RemoteException {
        Log.i("ExampleServiceManager", "W - getAverageGpuTemperature");
        return service.getAverageGpuTemperature();
    }

    public Float getAverageAmbientTemperature() throws RemoteException {
        Log.i("ExampleServiceManager", "W - getAverageAmbientTemperature");
        return service.getAverageAmbientTemperature();
    }

    public Float getMaxCpuTemperature() throws RemoteException {
        Log.i("ExampleServiceManager", "W - getMaxCpuTemperature");
        return service.getMaxCpuTemperature();
    }

    public Float getMaxGpuTemperature() throws RemoteException {
        Log.i("ExampleServiceManager", "W - getMaxGpuTemperature");
        return service.getMaxGpuTemperature();
    }

    public Float getMaxAmbientTemperature() throws RemoteException {
        Log.i("ExampleServiceManager", "W - getMaxAmbientTemperature");
        return service.getMaxAmbientTemperature();
    }
}