from django.db import models
from django.contrib.auth.models import AbstractBaseUser, BaseUserManager
from django.contrib.auth.password_validation import validate_password
# Create your models here.

class UserManager(BaseUserManager):
    """
    The class is to override the django admin system its inheritance from BaseUserModel inthe class we have 2 definitions 
    the first one is to create a normal user by normal user  and to create a superuser that can effect the permission after that if needed

    """
    def create_user(self, email, first_name, last_name , password=None):
        """
        create a normal user the is staff field is set to false 
        """
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
        """
        the super user is an Admin and can modify all operations in the App(Delete, update, create)
        """
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
    """
    the class inheritance from the BaseUser  and will create a Table in the database for the user 
    the password is required by default in django and thats the reason why we donot have here an field for password
    the user name field is the email field and the required fielder are (email, first_name, last_name and the password)
    """
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