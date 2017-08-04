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
import android.widget.ArrayAdapter;
import android.widget.Spinner;

/* Activity for Colorfade Function
 */
public class ColorFadeActivity extends Fragment {
    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {


        View v = inflater.inflate(R.layout.menu_colorfade_main, container, false);

        String [] valuesfade =
                {"Always On","Stroboscope","Motion Detection"};
        String [] fadecolor =
                {"Red","Orange","Yellow","Green","Teal","Blue","Purple","Pink","White"};

        Spinner spinnerfade1 = (Spinner) v.findViewById(R.id.spinnerfade1);
        ArrayAdapter<String> adapter1 = new ArrayAdapter<String>(this.getActivity(), android.R.layout.simple_selectable_list_item, fadecolor);
        adapter1.setDropDownViewResource(android.R.layout.simple_list_item_single_choice);
        spinnerfade1.setAdapter(adapter1);

        Spinner spinnerfade2 = (Spinner) v.findViewById(R.id.spinnerfade2);
        ArrayAdapter<String> adapter2 = new ArrayAdapter<String>(this.getActivity(), android.R.layout.simple_selectable_list_item, fadecolor);
        adapter2.setDropDownViewResource(android.R.layout.simple_list_item_single_choice);
        spinnerfade2.setAdapter(adapter2);

        Spinner spinnerfade3 = (Spinner) v.findViewById(R.id.spinnerfade3);
        ArrayAdapter<String> adapter3 = new ArrayAdapter<String>(this.getActivity(), android.R.layout.simple_selectable_list_item, fadecolor);
        adapter3.setDropDownViewResource(android.R.layout.simple_list_item_single_choice);
        spinnerfade3.setAdapter(adapter3);

        Spinner spinnerfade= (Spinner) v.findViewById(R.id.spinnerfade);
        ArrayAdapter<String> adapterfade = new ArrayAdapter<String>(this.getActivity(), android.R.layout.simple_selectable_list_item, valuesfade);
        adapterfade.setDropDownViewResource(android.R.layout.simple_list_item_single_choice);
        spinnerfade.setAdapter(adapterfade);

        return  v;


    }
}
