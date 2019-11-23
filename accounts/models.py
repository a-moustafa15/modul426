from django.db import models
from django.contrib.auth.models import AbstractBaseUser, BaseUserManager
# Create your models here.

class UserManager(BaseUserManager):
    def create_user(self, email, first_name, last_name , password=None):
        if not email:
            raise ValueError ( 'Email field is required')

        user = self.model(
            email = self.normalize_email(email)
        )
        user.first_name= first_name
        user.last_name = last_name
        #user.is_staff = False
        user.set_password(password)
        user.save(using=self._db)
        return user

    def create_superuser(self, email, first_name, last_name, password ):
        user = self.create_user(
            email, 
            first_name=first_name,
            last_name=last_name,
            password=password,

            )
        user.is_staff=True
        
        user.save(using=self._db)
        return user

class User (AbstractBaseUser):
    email = models.EmailField(max_length=255, unique=True, blank=False, null=False)
    first_name = models.CharField(max_length=122, blank=False, null=False)
    last_name = models.CharField(max_length=122, blank=False, null=False)
    active = models.BooleanField(default=True)

    is_staff = models.BooleanField(default=False, blank=True, null=True)
    
    USERNAME_FIELD = 'email'
    REQUIRED_FIELDS = ['first_name', 'last_name']

    objects = UserManager()
  
    def __str__(self):
        return "{} {}".format(self.first_name, self.last_name)

    def has_perm(self, perm, obj=None):
        return True    

    def has_module_perms(self, app_label):
        return True         