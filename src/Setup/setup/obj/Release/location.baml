   M S B A M L   `   `   `  ���� @  <setup, Version=1.0.0.0, Culture=neutral, PublicKeyToken=nullclr-namespace:setupsetup      setup.location   R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     @d2http://schemas.microsoft.com/expression/blend/2008     %localclr-namespace:setup       N� Title$  location�� � 	Resources  �� 
TargetType   	submitbtn �� Property �� Value �� 
TargetType �� CornerRadius �� Triggers :� RoutedEvent	 �� TargetProperty	
 �� To g� Duration g� FillBehavior W� From	 W� To g� AutoReverse  btn��%�  &	        &	 =    �� " ��.���  � ��
 �������  � �� �#2983cc��  �@�Cursor$
 Hand����  � �� �� " ��.R��� #��z��$ 6��._��� $��Center=�$��Center=� :� $ Button.MouseEnter��[��� .���� .���� $1	 +(Button.Background).(SolidColorBrush.Color)�$
 #4f9dddX�$ 0:0:0.1D�$ HoldEnd=�:� $ Button.MouseLeave��[��� .���� .���� $1	 +(Button.Background).(SolidColorBrush.Color)�$
 #2983ccX�$ 0:0:0.1D�:� $ Button.Click��[��� .���� .��W� $	 (Button.Opacity)�$ 1X�$	 0.8X�$ 0:0:0.2D� . �� " ��.���  � �� �#000��  � �� �#ddd��  �@�Cursor$
 Hand����  � �� �� " ��.R��� #��z��$ 6��._��� $��Center=�$��Center=� :� $ Button.MouseEnter��[��� .���� .���� $1	 +(Button.Background).(SolidColorBrush.Color)�$
 #e7e7e7X�$ 0:0:0.1D�$ HoldEnd=�:� $ Button.MouseLeave��[��� .���� .���� $1	 +(Button.Background).(SolidColorBrush.Color)�$

 #dddX�$ 0:0:0.1D�:� $ Button.Click��[��� .���� .��W� $	 (Button.Opacity)�$ 1X�$	 0.7X�$ 0:0:0.2D� . .��� 
�������.+��� $
��Left=�$	��111��$��Center=�$	��115��$��	/logo.png��$��	55,0,0,40q� J� OpacityMask ��  �� ImageSource$ 	/logo.png�� j� TileMode$
 None=� j� Stretch$ Uniform=��� $��SecondDownloader��$
��Left=�$��
186,0,0,80q�$��Center=�$��Microsoft YaHei UI)�$��25(��� $��选择安装位置��$
��Left=�$��188,34,0,10q�$��Center=�$��Microsoft YaHei UI)�$��15(��� $ ��Developed by PinsoftStudio��$
��Left=�$��
188,0,0,24q�$��Center=�$��Cascadia Code)��� -   $��继续��#��[  $��Microsoft YaHei UI)�$��15(�$��	0,0,10,10q�$��60��$��35��$��Right=�$��Bottom=� �� 	ClickMode$ Press=��� -   $��浏览��#��[ $��Microsoft YaHei UI)�$��15(�$��	0,0,78,10q�$��60��$��35��$��Right=�$��Bottom=�$ Press=��� -    ��Name$ textbox��$��
10,0,157,9q� �� TextWrapping$ NoWrap=�$��TextBox��$��23��$��Bottom=�$��15(�