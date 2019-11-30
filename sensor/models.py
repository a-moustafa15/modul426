from django.db import models
import datetime
# Create your models here.

class Sensor(models.Model):

    movement = models.BooleanField(default=True)
    movment_date = models.DateTimeField(default=datetime.datetime.now())

    def __str__ (self):
        return str(self.movment_date)