from django.contrib import admin
from .models import User
from .forms import UserCreationForm
from django.contrib.auth.admin import UserAdmin as BaseUserAdmin
from django.contrib.auth.models import Group




class UserAdmin(BaseUserAdmin):
    """
    the class inheritance from the BaseUserAdmin Class it will effect how the admin site will looks like 
    """
 
    #form = UserUpdateForm
    add_form = UserCreationForm

    list_display = ('email',  'first_name', 'last_name', 'is_staff')
    list_filter = ('first_name',)
    fieldsets = (
        (None, {'fields': ('email', 'last_name', 'first_name')}),
      
    )

    add_fieldsets = (
        (None, {
            'classes': ('wide',),
            'fields': ('email', 'password', 'last_name', 'first_name')}),
           
    )
    search_fields = ('email',)
    ordering = ('email',)
    filter_horizontal = ()


admin.site.register(User, UserAdmin)
admin.site.unregister(Group)