class House:

    def __init__(self, id, name, location, capacity, price_per_night):
        self.__id = id
        self.__name = name
        self.__location = location
        self.__capacity = capacity
        self.__price_per_night = price_per_night

    def get_id(self):
        return self.__id

    def get_name(self):
        return self.__name

    def get_location(self):
        return self.__location

    def get_capacity(self):
        return self.__capacity

    def get_price_per_night(self):
        return self.__price_per_night

    def __str__(self):
        return "Id: " + str(self.__id) + '\n' + "Name: " + self.__name + '\n' + "Location: " + self.__location + '\n' + "Capacity: " + str(self.__capacity) + '\n' + "Price/night: " + str(self.__price_per_night)

class Inchiriere:

    def __init__(self, house, price):
        self.__house = house
        self.__price = price

    def get_nume(self):
        return self.__house.get_name()

    def get_price(self):
        return self.__price

    def set_casa(self, value):
        self.__house = value

    def set_price(self, value):
        self.__price = value

    def __str__(self):
       return "Name: " + self.get_nume() + '\n' + "Price: " + str(self.get_price())