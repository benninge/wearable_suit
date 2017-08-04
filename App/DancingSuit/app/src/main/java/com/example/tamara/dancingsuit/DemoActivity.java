package com.example.tamara.dancingsuit;

import android.content.Intent;
import android.content.res.ColorStateList;
import android.graphics.drawable.Drawable;
import android.os.Build;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.NavigationView;
import android.support.design.widget.Snackbar;
import android.support.v4.view.GravityCompat;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.View;
import android.view.Window;

import static android.R.drawable.ic_media_play;

/**
 * Created by Tamara on 26.07.17.
 */

public class DemoActivity extends AppCompatActivity {

    DrawerLayout dlayout;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.demo_main);


        Window window = getWindow();
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            window.setStatusBarColor(getColor(R.color.colorPrimaryDark));
        } else {
            window.setStatusBarColor(getResources().getColor((R.color.colorPrimaryDark)));
        }


        dlayout = (DrawerLayout)findViewById(R.id.drawer_layout);

        Toolbar myToolbar = (Toolbar) findViewById(R.id.toolbardemo);
        setSupportActionBar(myToolbar);
        getSupportActionBar().setTitle("Demo");

        getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        getSupportActionBar().setDisplayShowHomeEnabled(true);
        myToolbar.setNavigationOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(DemoActivity.this,MainActivity.class);
                startActivity(i);

            }
        });





    }
}
