from django.shortcuts import render, redirect

from django.views.generic import ListView, CreateView, DetailView
from .models import User
from django.views.generic import View
from django.contrib.auth.models import auth
from .forms import UserLoginForm, UserCreationForm
from django.contrib import messages



class CreateUser(CreateView):
    template_name = 'accounts/create_user.html'
    def get(self, request, *args, **kwargs):
        form = UserCreationForm()
        return render(request, self.template_name, {'form':form})

    def post(self, request,*args, **kwargs):
        form = UserCreationForm(request.POST or None)
        if form.is_valid():
            form.save()
            return redirect('.')
        return render(request, self.template_name, {'form':form})
        

class LogIn(View):
    """
    the class is to handel get and post method when a user want to login
    """
    template_name = 'accounts/login.html'

    def get(self, request, *args, **kwargs):
        """

        :param request: Url get request
        :return: will return an empty form (loginForm)
        """
        form = UserLoginForm()
        return render(request, self.template_name, {'form': form})

    def post(self, request, *args, **kwargs):
        """

        :param request: Url post request
        :return: will let the user login in case all the information in the form is valid
        """
        form = UserLoginForm(request.POST or None)
        email = request.POST['email']
        password = request.POST['password']
        user = auth.authenticate(email=email, password=password)
        if user is not None:
            auth.login(self.request, user)
            return redirect('homepage:homepage')
        else:
            messages.info(request, "invalid name or password")
            return redirect('accounts:login-user')
        return render(request, self.template_name, {'form': form})


class Logout(View):
    """
    the class is to logout a User
    """
    def get(self, request):
        """

        :param request: URl get request
        :return: logout
        """
        auth.logout(request)
        return redirect('accounts:login-user')


