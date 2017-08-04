package com.example.tamara.dancingsuit;

import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.view.Window;

/**
 * Created by Tamara on 26.07.17.
 */

public class ShareActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.share_main);

        Window window = getWindow();
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            window.setStatusBarColor(getColor(R.color.colorPrimaryDark));
        } else {
            window.setStatusBarColor(getResources().getColor((R.color.colorPrimaryDark)));
        }

        Toolbar myToolbar = (Toolbar) findViewById(R.id.toolbarshare);
        setSupportActionBar(myToolbar);
        getSupportActionBar().setTitle("Share");

        getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        getSupportActionBar().setDisplayShowHomeEnabled(true);
        myToolbar.setNavigationOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(ShareActivity.this,MainActivity.class);
                startActivity(i);
            }
        });


    }

}
