package com.example.prac10_1;

public class Contact {
    private int id; //идентификатор
    private String name;//имя
    private String phone;//номер телефона
    private String age;
    private String weight;
    public Contact(int id, String name, String phone, String age, String weight) {
        this.id = id;
        this.name = name;
        this.phone = phone;
        this.age = age;
        this.weight = weight;
    }
    public int getId() {
        return id;
    }
    public void setId(int id) {
        this.id = id;
    }
    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }
    public String getPhone() {
        return phone;
    }
    public void setPhone(String phone) {
        this.phone = phone;
    }
    public String getAge() {
        return age;
    }
    public void setAge(String _age) {
        this.age = _age;
    }
    public String  getWeight() {
        return weight;
    }
    public void setWeight(String _weight) {
        this.weight = _weight;
    }

}
