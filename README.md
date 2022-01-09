# teriyaki

Simple interpreter written in C



## Language Definition

### variable declaration.
```ruby

isCold as Boolean be false

address as String be "2123 H2L New York"

cometPeriod as Number be 23234

```


### Object declaration
```ruby
Object ZipCode has
  address as String
  country as String
  code as Number
end

Object Citizen  has
  socialNumber as Number
  address as String
  country as String
end



```


### Object initialization

```ruby

canadian as Citizen is
  socialNumber 000000012,
  address "4532 Rue St. Catherine",
  country "canada",
end
```

### Array Declaration

```ruby

postalCodes of ZipCode are
  ZipCode{"2434 Rue st.Denis","canada", 2345}
  ZipCode{"Carrera 64 #24-43, Barranquilla, Colombia","Colombia",  5000001}
end
```

### Function declaration

```ruby

func determineZipCode address as String, country as String returns Number, Boolean do
  being postalCode of postalCodes do
    being address in postalCode address do
      return code in postalCode, true
    being otherwise country in postalCode country do
      return code in postalCode, true
   otherwise do
     return -1, false
  end
end


func moveCitizen citizen as Citizen do
  being country in citizen "Palestine" do
    country in citizen be "Canada"
end

```


