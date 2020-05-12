package platis.solutions.localDeviceNameResolution;

import androidx.appcompat.app.AppCompatActivity;

import android.net.nsd.NsdManager;
import android.os.Bundle;
import android.util.Log;

import java.net.InetAddress;
import java.util.concurrent.TimeUnit;

public class MainActivity extends AppCompatActivity {
    private String TAG = "smartcar";
    NsdManager mNsdManager;

    LocalNetworkDeviceNameResolver mDeviceNameResolver;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Don't use the same device name for multiple instances as they overwrite each other
        // Asynchronous device name resolution (suggested)
        mDeviceNameResolver =
                new LocalNetworkDeviceNameResolver(this.getApplicationContext(),
                        "smartcar", "_http._tcp.", 80,
                        new LocalNetworkDeviceNameResolver.AddressResolutionListener() {
                            @Override
                            public void onAddressResolved(InetAddress address) {
                                Log.i(TAG, "Asynchronous IP resolution: " + address.getHostName
                                        ());
                            }
                        });

        // Synchronous device name resolution
        final LocalNetworkDeviceNameResolver nameResolver =
                new LocalNetworkDeviceNameResolver(this.getApplicationContext(),
                        "someServicesThatDoNotExistWillThrowAfterTimeout", "_http._tcp.", 80);
        Thread t = new Thread() {
            public void run() {
                try {
                    InetAddress address = nameResolver.getAddress(10, TimeUnit.SECONDS);
                    Log.i(TAG, "Synchronous IP resolution: " + address.getHostName());
                } catch (DeviceNameNotResolvedException e) {
                    Log.e(TAG, e.toString());
                }
            }
        };
        t.start();
    }
}
