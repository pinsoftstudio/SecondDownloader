   M S B A M L   `   `   `  ���� A  =Update, Version=1.0.0.0, Culture=neutral, PublicKeyToken=nullclr-namespace:UpdateUpdate      Update.NoNeed   R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     @d2http://schemas.microsoft.com/expression/blend/2008     &localclr-namespace:Update       N� Title$  NoNeed�� � 	Resources  �� 
TargetType   	submitbtn �� Property �� Value �� 
TargetType �� CornerRadius �� Triggers :� RoutedEvent	 �� TargetProperty	
 �� To g� Duration g� FillBehavior W� From	 W� To g� AutoReverse��%G  &	        �� " ��.���  � ��
 �������  � �� �#2983cc��  �@�Cursor$
 Hand����  � �� �� " ��.R��� #��z��$ 6��._��� $��Center=�$��Center=� :� $ Button.MouseEnter��[��� .���� .���� $1	 +(Button.Background).(SolidColorBrush.Color)�$
 #4f9dddX�$ 0:0:0.1D�$ HoldEnd=�:� $ Button.MouseLeave��[��� .���� .���� $1	 +(Button.Background).(SolidColorBrush.Color)�$
 #2983ccX�$ 0:0:0.1D�:� $ Button.Click��[��� .���� .��W� $	 (Button.Opacity)�$ 1X�$	 0.8X�$ 0:0:0.2D� . .��� 
�������.+��� $
��Left=�$��20��$��10,1,0,0q�$	��Top=�$��22��$��	/icon.ico�� J� OpacityMask ��  �� ImageSource$ /update.png�� j� Stretch$ Uniform=��� $��在线升级��$
��Left=�$��	40,-4,0,0q�$	��Top=�$	��177��$��15(�$��34���� $��您已经是最新版本��$
��Left=�$��
138,88,0,0q�$	��Top=�$	��286��$��20(����� �� $
��Left=�$	��142��$��154,158,0,0q�$	��Top=�$	��151��$��/update.png���� -    ��Name$ btnOK��$��好的��#��[  $��Microsoft YaHei UI)�$��15(�$��	0,477,0,0q�$	��212��$��35��$��Center=�$	��Top=� �� 	ClickMode$ Press=��� -    ��Name$ 
labversion��$��最新版本��$��Center=�$��	0,382,0,0q�$	��Top=�$	��286��$��20(�$��Center=�$��Center=����� 