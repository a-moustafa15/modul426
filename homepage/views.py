from django.shortcuts import render
from django.views.generic import View
# Create your views here.

class HomePage(View):
    template_name = 'homepage/home_page.html'

    def get (self, request, *args, **kwargs):
        return render(request, self.template_name)
