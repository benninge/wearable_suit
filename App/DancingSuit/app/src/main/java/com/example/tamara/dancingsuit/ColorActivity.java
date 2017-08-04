package com.example.tamara.dancingsuit;
/**
 * Created by Tamara on 27.07.17.
 */

import android.app.Activity;
import android.graphics.Color;
import android.media.Image;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentActivity;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.CheckBox;
import android.widget.Spinner;
import android.widget.Toast;

/* Activity for Color Function
 */

public class ColorActivity extends Fragment {
    Spinner spinner;
    private static final String LOG_TAG = "";
    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {



        final View v = inflater.inflate(R.layout.menu_color_main, container, false);

        String [] values =
                {"Always On","Stroboscope","Motion Detection"};
        final Spinner spinner = (Spinner) v.findViewById(R.id.spinnercoloractivity);
        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this.getActivity(), android.R.layout.simple_selectable_list_item, values);
        adapter.setDropDownViewResource(android.R.layout.simple_list_item_single_choice);
        spinner.setAdapter(adapter);

        spinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parentView, View selectedItemView, int position, long id) {

                String text = spinner.getSelectedItem().toString();
                Log.d(LOG_TAG,
                        "Blinking-Pattern" + text);
            }

            @Override
            public void onNothingSelected(AdapterView<?> parentView) {
                // your code here
            }

        });

        return v;

    }
    // get checked colors
    /*public void onCheckboxClicked(View view) {
        // Is the view now checked?
        boolean checked = ((CheckBox) view).isChecked();

        // Check which checkbox was clicked
        switch(view.getId()) {
            case R.id.checkBoxRed:
                if (checked) {
                }
                else
                    break;
            case R.id.checkBoxOrange:
                if (checked) {
                }
                else
                    break;
            case R.id.checkBoxYellow:
                if (checked) {
                }
                else
                    break;
            case R.id.checkBoxGreen:
                if (checked) {
                }
                else
                    break;
            case R.id.checkBoxTeal:
                if (checked) {
                }
                else
                    break;
            case R.id.checkBoxBlue:
                if (checked) {
                }
                else
                    break;
            case R.id.checkBoxPurple:
                if (checked) {
                }
                else
                    break;
            case R.id.checkBoxPink:
                if (checked) {
                }
                else
                    break;
            case R.id.checkBoxWhite:
                if (checked) {
                }
                else
                    break;

        }*/
}
