package com.example.prac6;

import android.content.Intent;
import android.os.Bundle;
import android.view.MenuItem;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.annotation.NonNull;
import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.ActionBarDrawerToggle;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;
import androidx.drawerlayout.widget.DrawerLayout;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;
import androidx.navigation.NavController;
import androidx.navigation.Navigation;
import androidx.navigation.ui.NavigationUI;

import com.example.prac6.databinding.ActivityMainBinding;
import com.google.android.material.bottomnavigation.BottomNavigationView;
import com.google.android.material.navigation.NavigationView;

public class DrawerActivity extends AppCompatActivity {
    ActionBarDrawerToggle toggle;
    ActionBar actionBar;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_drawer);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.drawer_layout), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });

        DrawerLayout drawer = findViewById(R.id.drawer_layout);
        toggle = new ActionBarDrawerToggle(
                DrawerActivity.this, drawer, R.string.drawer_open,
                R.string.drawer_close);
        if (drawer != null) {
            drawer.addDrawerListener(toggle);
        }
        NavigationView navView =  drawer.findViewById(R.id.nav_view);
        toggle.syncState();
// to make the Navigation drawer icon always appear on the action bar
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        actionBar = getSupportActionBar();
        FragmentManager fragmentManager = getSupportFragmentManager();
        fragmentManager.beginTransaction().add(R.id.content_frame, BaseFragment.class, null).commit();

        navView.setNavigationItemSelectedListener(new NavigationView.OnNavigationItemSelectedListener() {
            @Override
            public boolean onNavigationItemSelected(@NonNull MenuItem item) {
                // Обработка нажатий
                int id = item.getItemId();
                if (id == R.id.nav_home) {
                    FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();
                    ImageFragment fragment = new ImageFragment();
                    fragmentTransaction.replace(R.id.content_frame, fragment);
                    actionBar.setTitle("prac6 " + item.getTitle().toString());
                    fragmentTransaction.commit();
                } else if (id == R.id.nav_setting) {
                    FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();
                    ImageFearlessFragment fragment = new ImageFearlessFragment();
                    fragmentTransaction.replace(R.id.content_frame, fragment);
                    actionBar.setTitle("prac6 " + item.getTitle().toString());
                    fragmentTransaction.commit();
                } else if (id == R.id.nav_notifications) {
                    FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();
                    HandsomeFragment fragment = new HandsomeFragment();
                    fragmentTransaction.replace(R.id.content_frame, fragment);
                    actionBar.setTitle("prac6 " + item.getTitle().toString());
                    fragmentTransaction.commit();
                } else if (id == R.id.nav_next_activity){
                    Intent intent = new Intent(DrawerActivity.this, MainActivity.class);
                    startActivity(intent);
                }
                // Закрыть Navigation Drawer после выбора элемента
                drawer.closeDrawers();

                // Возвращаем true, чтобы указать, что событие обработано
                return true;
            }
        });
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        if (toggle.onOptionsItemSelected(item)) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }
}
