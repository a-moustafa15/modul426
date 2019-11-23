
from django.urls import path
from .views import  CreateUser, LogIn, Logout
from django.contrib.auth.decorators import login_required


app_name = 'accounts'

urlpatterns = [

    path('create/', CreateUser.as_view(), name='create-user'),
    path('login/', LogIn.as_view(), name='login-user'),
    path("logout/", Logout.as_view(), name="logout"),







]