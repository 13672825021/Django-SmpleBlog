# Generated by Django 2.0.4 on 2018-04-13 15:06

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('app_R_and_L', '0005_auto_20180413_2300'),
    ]

    operations = [
        migrations.AlterField(
            model_name='comment',
            name='commentID',
            field=models.AutoField(primary_key=True, serialize=False),
        ),
        migrations.AlterField(
            model_name='user',
            name='userID',
            field=models.AutoField(primary_key=True, serialize=False),
        ),
    ]
