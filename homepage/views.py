from django.shortcuts import render
from django.views.generic import View
# Create your views here.

class HomePage(View):
    """
    the class inheritance from a generic view and it is a normal view to create the homepage (landing page)
    """
    template_name = 'homepage/home_page.html'

    def get (self, request, *args, **kwargs):
        return render(request, self.template_name)
