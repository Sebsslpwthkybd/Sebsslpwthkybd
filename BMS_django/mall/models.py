from django.db import models
from django.contrib.contenttypes.models import ContentType
from django.contrib.contenttypes.fields import GenericForeignKey, GenericRelation

# Create your models here.


class Item(models.Model):
    item_id = models.IntegerField(verbose_name='id', db_column='id', primary_key=True)
    item_name = models.CharField(verbose_name='name', db_column='name', null=False, max_length=100)
    item_quantity = models.IntegerField(verbose_name='quantity', db_column='quantity', null=False, default=0)
    item_brief = models.TextField(verbose_name='brief', db_column='brief', null=True)
    item_price = models.DecimalField(verbose_name='price', db_column='price', max_digits=8, decimal_places=2, null=False, default=0.00)

    class Meta:
        db_table = 'goods'


class Comment(models.Model):
    id = models.ForeignKey(ContentType, on_delete=models.CASCADE)
    score = models.IntegerField(default=5)
