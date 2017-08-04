package com.example.tamara.dancingsuit;

/**
 * Created by Tamara on 27.07.17.
 */

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

/* Activity for Autocolorfade Function
 */
public class AutoColorFadeActivity extends Fragment {
    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        return  inflater.inflate(R.layout.menu_autocolorfade_main,container,false);
    }
}
