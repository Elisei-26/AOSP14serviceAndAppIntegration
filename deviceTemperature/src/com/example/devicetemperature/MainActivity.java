package com.example.devicetemperature;

import android.os.Bundle;
import android.os.RemoteException;
import android.util.Log;
import android.widget.TextView;
import androidx.appcompat.app.AppCompatActivity;
import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.util.Timer;
import java.util.TimerTask;

import example.service.manager.ExampleServiceManager;

public class MainActivity extends AppCompatActivity {
    private ExampleServiceManager exampleManager = ExampleServiceManager.GetInstance();
    private Timer timer;
    private NumberFormat formatter = new DecimalFormat("#0.00");
    
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Log.i("ExampleClientApp: ", "Started in onCreate");
    }

    @Override
    protected void onResume() {
        super.onResume();
        startTimer(true);
    }

    @Override
    protected void onPause() {
        super.onPause();
        startTimer(false);
    }

    private void displayCpuTemperature() {
        try {
            Float valueCpu = exampleManager.GetCpuTemperature();
            String textView = "CPU Temperature: " + formatter.format(valueCpu);
            ((TextView)findViewById(R.id.textView1)).setText(textView);
        } catch (RemoteException e) {
            Log.e("ExampleClientApp: ", "Error when trying to access binder!");
            e.printStackTrace();
        }
    }

    private void displayGpuTemperature() {
        try {
            Float valueGpu = exampleManager.GetGpuTemperature();
            String textView = "GPU Temperature: " + formatter.format(valueGpu);
            ((TextView)findViewById(R.id.textView2)).setText(textView);
        } catch (RemoteException e) {
            Log.e("ExampleClientApp: ", "Error when trying to access binder!");
            e.printStackTrace();
        }
    }

    private void displayAmbientTemperature() {
        try {
            Float valueAmbient = exampleManager.GetAmbientTemperature();
            String textView = "Ambient Temperature: " + formatter.format(valueAmbient);
            ((TextView)findViewById(R.id.textView3)).setText(textView);
        } catch (RemoteException e) {
            Log.e("ExampleClientApp: ", "Error when trying to access binder!");
            e.printStackTrace();
        }
    }

    private void displayAverageCpuTemperature() {
        try {
            Float valueAverageCpu = exampleManager.GetAverageCpuTemperature();
            String textView = "CPU Average Temperature: " + formatter.format(valueAverageCpu);
            ((TextView)findViewById(R.id.textView4)).setText(textView);
        } catch (RemoteException e) {
            Log.e("ExampleClientApp: ", "Error when trying to access binder!");
            e.printStackTrace();
        }
    }

    private void displayAverageGpuTemperature() {
        try {
            Float valueAverageGpu = exampleManager.GetAverageGpuTemperature();
            String textView = "GPU Average Temperature: " + formatter.format(valueAverageGpu);
            ((TextView)findViewById(R.id.textView5)).setText(textView);
        } catch (RemoteException e) {
            Log.e("ExampleClientApp: ", "Error when trying to access binder!");
            e.printStackTrace();
        }
    }

    private void displayAverageAmbientTemperature() {
        try {
            Float valueAverageAmbient = exampleManager.GetAverageAmbientTemperature();
            String textView = "Ambient Average Temperature: " + formatter.format(valueAverageAmbient);
            ((TextView)findViewById(R.id.textView6)).setText(textView);
        } catch (RemoteException e) {
            Log.e("ExampleClientApp: ", "Error when trying to access binder!");
            e.printStackTrace();
        }
    }

    private void displayMaxCpuTemperature() {
        try {
            Float valueMaxCpu = exampleManager.GetMaxCpuTemperature();
            String textView = "Max CPU Temperature: " + formatter.format(valueMaxCpu);
            ((TextView)findViewById(R.id.textView7)).setText(textView);
        } catch (RemoteException e) {
            Log.e("ExampleClientApp: ", "Error when trying to access binder!");
            e.printStackTrace();
        }
    }

    private void displayMaxGpuTemperature() {
        try {
            Float valueMaxGpu = exampleManager.GetMaxGpuTemperature();
            String textView = "Max GPU Temperature: " + formatter.format(valueMaxGpu);
            ((TextView)findViewById(R.id.textView8)).setText(textView);
        } catch (RemoteException e) {
            Log.e("ExampleClientApp: ", "Error when trying to access binder!");
            e.printStackTrace();
        }
    }

    private void displayMaxAmbientTemperature() {
        try {
            Float valueMaxAmbient = exampleManager.GetMaxAmbientTemperature();
            String textView = "Max Ambient Temperature: " + formatter.format(valueMaxAmbient);
            ((TextView)findViewById(R.id.textView9)).setText(textView);
        } catch (RemoteException e) {
            Log.e("ExampleClientApp: ", "Error when trying to access binder!");
            e.printStackTrace();
        }
    }

    private void startTimer(boolean toStart) {
        if (toStart) {
            timer = new Timer();
            timer.schedule(new TimerTask() {
                @Override
                public void run() {
                    runOnUiThread(() -> {
                        displayCpuTemperature();
                        displayGpuTemperature();
                        displayAmbientTemperature();
                        displayAverageCpuTemperature();
                        displayAverageGpuTemperature();
                        displayAverageAmbientTemperature();
                        displayMaxCpuTemperature();
                        displayMaxGpuTemperature();
                        displayMaxAmbientTemperature();
                    });
                }
            }, 0, 1000);
        } else {
            timer.cancel();
            timer.purge();
        }
    }
}