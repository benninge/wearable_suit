package com.example.tamara.dancingsuit;

import android.app.Activity;
import android.content.Intent;
import android.icu.text.IDNA;
import android.os.Build;
import android.os.Bundle;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;


/**
 * Created by Tamara on 26.07.17.
 */

public class InfoActivity extends AppCompatActivity{
boolean check;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.info_main);

        Window window = getWindow();
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            window.setStatusBarColor(getColor(R.color.colorPrimaryDark));
        } else {
            window.setStatusBarColor(getResources().getColor((R.color.colorPrimaryDark)));
        }

        Toolbar myToolbar = (Toolbar) findViewById(R.id.toolbarinfo);
        setSupportActionBar(myToolbar);
        getSupportActionBar().setTitle("Info");

        getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        getSupportActionBar().setDisplayShowHomeEnabled(true);
        myToolbar.setNavigationOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(InfoActivity.this,MainActivity.class);
                startActivity(i);
            }
        });

    }
}
