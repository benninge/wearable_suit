package com.example.tamara.dancingsuit;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.content.res.ColorStateList;
import android.graphics.Color;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.util.Log;
import android.view.View;
import android.support.design.widget.NavigationView;
import android.support.v4.view.GravityCompat;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;

import static android.R.drawable.ic_lock_power_off;
import static android.R.drawable.ic_media_play;

public class MainActivity extends AppCompatActivity
        implements NavigationView.OnNavigationItemSelectedListener {

    // UUID for commmunication with serial modul
    private UUID uuid = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    // comments on app status
    private static final String LOG_TAG = "";
    boolean check = false;
    // variables for bluetooth
    private BluetoothAdapter adapter = null;
    private BluetoothSocket socket = null;
    private OutputStream stream_out = null;
    private InputStream stream_in = null;
    private boolean is_connected = false;
    private static String mac_adresse; // MAC adress of bluethooth modul

    DrawerLayout dlayout;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        dlayout = (DrawerLayout)findViewById(R.id.drawer_layout);

        //-----------------------connection to bluethooth adapter------------------
        /*Log.d(LOG_TAG, "Bluetest: OnCreate");
        // Connection with Bluetooth-Adapter
        adapter = BluetoothAdapter.getDefaultAdapter();
        if (adapter == null || !adapter.isEnabled()) {
            Toast.makeText(this, "Please enable Bluetooth",
                    Toast.LENGTH_LONG).show();
            Log.d(LOG_TAG,
                    "onCreate: Bluetooth Error: Deactivated or not available");
            finish();
            return;
        } else
            Log.d(LOG_TAG, "onCreate: Bluetooth-Adapter is ready to connect");*/
        dlayout.setBackgroundResource(R.drawable.suiton);

        final FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fabon);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {


                if (check == false) {
                    Snackbar.make(view, "Connection to Suit failed", Snackbar.LENGTH_LONG)
                            .setAction("Action", null).show();
                    dlayout.setBackgroundResource(R.drawable.suiton);
                    fab.setImageResource(ic_media_play);
                    fab.setBackgroundTintList(ColorStateList.valueOf(getResources().getColor(R.color.colorPrimary)));
                    check = true;
                }
                else {
                    Snackbar.make(view, "Dance...!", Snackbar.LENGTH_LONG)
                            .setAction("Action", null).show();
                }
            }
        });

        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        ActionBarDrawerToggle toggle = new ActionBarDrawerToggle(
                this, drawer, toolbar, R.string.navigation_drawer_open, R.string.navigation_drawer_close);
        drawer.setDrawerListener(toggle);
        toggle.syncState();

        NavigationView navigationView = (NavigationView) findViewById(R.id.nav_view);
        navigationView.setNavigationItemSelectedListener(this);

    }

    /*public void connect(View view){

        mac_adresse = "00:12:03:31:02:24";  //our bluetooth modul
        Log.d(LOG_TAG, "Connect with " + mac_adresse);

        BluetoothDevice remote_device = adapter.getRemoteDevice(mac_adresse);

        // build socket
        try {
            socket = remote_device
                    .createInsecureRfcommSocketToServiceRecord(uuid);
            Log.d(LOG_TAG, "Socket successfully build");
        } catch (Exception e) {
            Log.e(LOG_TAG, "Socket building failed: " + e.toString());
        }

        adapter.cancelDiscovery();

        // socket connect
        try {
            socket.connect();
            Log.d(LOG_TAG, "Socket connected");
            is_connected = true;
        } catch (IOException e) {
            is_connected = false;
            Log.e(LOG_TAG, "Unable to connect socket " + e.toString());
        }

        // Socket beenden, falls nicht verbunden werden konnte
        if (!is_connected) {
            try {
                socket.close();
            } catch (Exception e) {
                Log.e(LOG_TAG,
                        "Socket can not be canceled: " + e.toString());
            }
        }

        // Outputstream erstellen:
        try {
            stream_out = socket.getOutputStream();
            Log.d(LOG_TAG, "OutputStream generated");
        } catch (IOException e) {
            Log.e(LOG_TAG, "OutputStream error: " + e.toString());
            is_connected = false;
        }

        // Inputstream erstellen
        try {
            stream_in = socket.getInputStream();
            Log.d(LOG_TAG, "InputStream generated");
        } catch (IOException e) {
            Log.e(LOG_TAG, "InputStream error: " + e.toString());
            is_connected = false;
        }

        if (is_connected) {
            Toast.makeText(this, "Connected with " + mac_adresse,
                    Toast.LENGTH_LONG).show();

        } else {
            Toast.makeText(this, "Connection to " + mac_adresse + "failed",
                    Toast.LENGTH_LONG).show();

        }


    }*/

    @Override
    public void onBackPressed() {
        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        if (drawer.isDrawerOpen(GravityCompat.START)) {
            drawer.closeDrawer(GravityCompat.START);
        } else {
            super.onBackPressed();
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_disconnect) {
            final FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fabon);

            dlayout.setBackgroundResource(R.drawable.backgroundblack);
            fab.setImageResource(ic_lock_power_off);
            fab.setBackgroundTintList(ColorStateList.valueOf(getResources().getColor(R.color.green)));
            check = false;
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    @SuppressWarnings("StatementWithEmptyBody")
    @Override
    public boolean onNavigationItemSelected(MenuItem item) {
        // Handle navigation view item clicks here.
        int id = item.getItemId();

        if (id == R.id.nav_right_arm) {
            Intent i = new Intent(MainActivity.this,MenuActivity.class);
            startActivity(i);


        } else if (id == R.id.nav_left_arm) {
            Intent i = new Intent(MainActivity.this,MenuActivity.class);
            startActivity(i);

        } else if (id == R.id.nav_right_leg) {
            Intent i = new Intent(MainActivity.this,MenuActivity.class);
            startActivity(i);

        } else if (id == R.id.nav_left_leg) {
            Intent i = new Intent(MainActivity.this,MenuActivity.class);
            startActivity(i);


        } else if (id == R.id.nav_hole_suit) {
            Intent i = new Intent(MainActivity.this,MenuActivity.class);
            startActivity(i);


        } else if (id == R.id.nav_slideshow) {
            Intent i = new Intent(MainActivity.this,DemoActivity.class);
            startActivity(i);

        } else if (id == R.id.nav_info) {
            Intent i = new Intent(MainActivity.this,InfoActivity.class);
            startActivity(i);

        } else if (id == R.id.nav_share) {
            Intent i = new Intent(MainActivity.this,ShareActivity.class);
            startActivity(i);
        }

        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        drawer.closeDrawer(GravityCompat.START);
        return true;
    }

    public void transmit(View v, String values) {
        String message = "Colorvalues"; // get the values ftom the 3 activities, color , colorfade, autocolorfade
        byte[] msgBuffer = message.getBytes();
        if (is_connected) {
            Log.d(LOG_TAG, "Send values: " + message);
            try {
                stream_out.write(msgBuffer);
            } catch (IOException e) {
                Log.e(LOG_TAG,
                        "Error while sending: " + e.toString());
            }
        }
    }

    public void recieve(View v) {
        byte[] buffer = new byte[1024]; // Puffer
        int laenge; // number of revieced bytes
        String msg = "";
        try {
            if (stream_in.available() > 0) {
                laenge = stream_in.read(buffer);
                Log.d(LOG_TAG,
                        "Number of revieced bytes: " + String.valueOf(laenge));


                for (int i = 0; i < laenge; i++)
                    msg += (char) buffer[i];

                Log.d(LOG_TAG, "Message: " + msg);
                Toast.makeText(this, msg, Toast.LENGTH_LONG).show();

            } else
                Toast.makeText(this, "Nothing recieve", Toast.LENGTH_LONG)
                        .show();
        } catch (Exception e) {
            Log.e(LOG_TAG, "Error while recieving: " + e.toString());
        }
    }

    public void disconnect(View v) {
        if (is_connected && stream_out != null) {
            is_connected = false;
            Log.d(LOG_TAG, "Disconnect");
            try {
                stream_out.flush();
                socket.close();
            } catch (IOException e) {
                Log.e(LOG_TAG,
                        "Error while disconnecting"
                                + e.toString());
            }
        } else
            Log.d(LOG_TAG, "Disconnect: no connection available");
    }
}
