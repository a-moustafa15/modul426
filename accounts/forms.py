from django.contrib.auth.forms import ReadOnlyPasswordHashField
from django import forms
from .models import User



class UserLoginForm(forms.ModelForm):
    password = forms.CharField(label='Password', widget=forms.PasswordInput)    
    class Meta:
        model = User
        fields = ['email', 'password']

class UserCreationForm(forms.ModelForm):
    """A form for creating new users. Includes all the required
    fields, plus a repeated password."""
    email = forms.EmailField(label='Email', required=True)
    password = forms.CharField(label='Password',required=True, widget=forms.PasswordInput())
    first_name = forms.CharField(label='First Name',required=True, widget=forms.TextInput())
    last_name = forms.CharField(label='Last Name',required=True, widget=forms.TextInput())



    class Meta:
        model = User
        fields = ('email','password','first_name','last_name' )

    def save(self,commit=True):
        # Save the provided password in hashed format
        user = super(UserCreationForm, self).save(commit=False)
        user.set_password(self.cleaned_data["password"])

        

        if commit:
            user.save()
        return user


class UserUpdateForm(forms.ModelForm):
    """A form for updating users. Includes all the fields on
    the user, but replaces the password field with admin's
    password hash display field.
    """
    #password = ReadOnlyPasswordHashField()
    email = forms.EmailField(label='Email', required=True)
   # password = forms.CharField(label='Password',required=True, widget=forms.PasswordInput())
    first_name = forms.CharField(label='First Name',required=True, widget=forms.TextInput())
    last_name = forms.CharField(label='Last Name',required=True, widget=forms.TextInput())
    is_staff = forms.BooleanField(label='Staff',required=False, widget=forms.CheckboxInput())


    class Meta:
        model = User
        exclude = ('last_login','password','active')
'''
    def clean_password(self):
        # Regardless of what the user provides, return the initial value.
        # This is done here, rather than on the field, because the
        # field does not have access to the initial value
        return self.initial["password"]

'''