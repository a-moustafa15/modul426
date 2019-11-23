from django.contrib import admin
from .models import User
from .forms import UserUpdateForm,UserCreationForm
from django.contrib.auth.admin import UserAdmin as BaseUserAdmin
from django.contrib.auth.models import Group
# Register your models here.



class UserAdmin(BaseUserAdmin):
    # The forms to add and change user instances
    form = UserUpdateForm
    add_form = UserCreationForm

    # The fields to be used in displaying the User model.
    # These override the definitions on the base UserAdmin
    # that reference specific fields on auth.User.
    list_display = ('email',  'first_name', 'last_name', 'is_staff')
    list_filter = ('first_name',)
    fieldsets = (
        (None, {'fields': ('email', 'last_name', 'first_name')}),
      
    )
    # add_fieldsets is not a standard ModelAdmin attribute. UserAdmin
    # overrides get_fieldsets to use this attribute when creating a user.
    add_fieldsets = (
        (None, {
            'classes': ('wide',),
            'fields': ('email', 'password', 'last_name', 'first_name')}),
           
    )
    search_fields = ('email',)
    ordering = ('email',)
    filter_horizontal = ()

# Now register the new UserAdmin...
admin.site.register(User, UserAdmin)
# ... and, since we're not using Django's built-in permissions,
# unregister the Group model from admin.
admin.site.unregister(Group)