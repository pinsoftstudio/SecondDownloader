   M S B A M L   `   `   `  ���� A  =Update, Version=1.0.0.0, Culture=neutral, PublicKeyToken=nullclr-namespace:UpdateUpdate      Update.Updating   R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     @d2http://schemas.microsoft.com/expression/blend/2008     U QWpfAnimatedGif, Version=2.0.0.0, Culture=neutral, PublicKeyToken=9e7cd3b544a090dc,gif"http://wpfanimatedgif.codeplex.com   localclr-namespace:Update    N� Title$  Updating�� � 	Resources  �� 
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
��Left=�$��20��$��10,1,0,0q�$	��Top=�$��22��$��	/icon.ico�� J� OpacityMask ��  �� ImageSource$ /update.png�� j� Stretch$ Uniform=��� $��在线升级��$
��Left=�$��	40,-4,0,0q�$	��Top=�$	��177��$��15(�$��34���� $��正在更新
��$
��Left=�$��
178,91,0,0q�$	��Top=�$	��286��$��20(�$��34������ �� "  WpfAnimatedGif.ImageBehavior   AnimatedSource$ /loading.gif��$��77,34,92,130q��� -    ��Name$ 
labVersion��$��最新版本��$��Center=�$��	0,398,0,0q�$	��Top=�$	��232��$��20(�$��Center=����� �� -   $ labelStatus��$��正在准备下载：��$��Center=�$��	0,525,0,0q�$	��Top=�$	��430��$��15(�� -    �Name$ progressbar��$��19��$��
10,0,10,10q�$��Bottom=����	#FF2983CC���#eee��Z� �� $��27��$��6,0,6,6q�$��Bottom=�
�������$��4�� �� RadiusX$ 9�� �� RadiusY$	 8.7��