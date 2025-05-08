package com.example.prac6;

import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Toast;

import com.example.prac6.ui.dashboard.DashboardFragment;
import com.google.android.material.bottomnavigation.BottomNavigationView;

import androidx.annotation.NonNull;
import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;
import androidx.navigation.NavController;
import androidx.navigation.Navigation;
import androidx.navigation.ui.AppBarConfiguration;
import androidx.navigation.ui.NavigationUI;

import com.example.prac6.databinding.ActivityMainBinding;
import com.google.android.material.navigation.NavigationView;

public class MainActivity extends AppCompatActivity {

    private ActivityMainBinding binding;
    ActionBar actionBar;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        BottomNavigationView navView = findViewById(R.id.nav_view);
        FragmentManager fragmentManager = getSupportFragmentManager();
        // Passing each menu ID as a set of Ids because each
        // menu should be considered as top level destinations.
        AppBarConfiguration appBarConfiguration = new AppBarConfiguration.Builder(
                R.id.navigation_home, R.id.navigation_dashboard, R.id.navigation_notifications)
                .build();
        actionBar = getSupportActionBar();
        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        navView.setOnNavigationItemSelectedListener(new BottomNavigationView.OnNavigationItemSelectedListener(){
            @Override
            public boolean onNavigationItemSelected(@NonNull MenuItem item) {
                // Обработка нажатий
                int id = item.getItemId();

                if (id == R.id.navigation_home){
                    FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();
                    LeftFragment fragment = new LeftFragment();
                    fragmentTransaction.replace(R.id.nav_host_fragment_activity_main, fragment);
                    fragmentTransaction.commit();
                    actionBar.setTitle("Home");
                } else if (id == R.id.navigation_notifications){
                    FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();
                    MiddleFragment fragment = new MiddleFragment();
                    fragmentTransaction.replace(R.id.nav_host_fragment_activity_main, fragment);
                    fragmentTransaction.commit();
                    actionBar.setTitle("Notifications");
                } else if (id == R.id.navigation_dashboard){
                    FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();
                    RightFragment fragment = new RightFragment();
                    fragmentTransaction.replace(R.id.nav_host_fragment_activity_main, fragment);
                    fragmentTransaction.commit();
                    actionBar.setTitle("Dashboard");
                }
                // Возвращаем true, чтобы указать, что событие обработано
                return true;
            }
        });
    }
}
