   M S B A M L   `   `   `  ����A  =Update, Version=1.0.0.0, Culture=neutral, PublicKeyToken=nullclr-namespace:UpdateUpdate  5          Update.NoNeed   5      R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5      R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5      Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5      @d2http://schemas.microsoft.com/expression/blend/2008     5      &localclr-namespace:Update     5        N� Title$  NoNeed��5	       � 	Resources 5
       �� 
TargetType   	submitbtn �� Property �� Value �� 
TargetType �� CornerRadius �� Triggers :� RoutedEvent	 �� TargetProperty	
 �� To g� Duration g� FillBehavior W� From	 W� To g� AutoReverse��%/  &	        �� 5   
   " ��6   .�5      ��  � ��
 �����6+   �� 5       � �� �#2983cc6+   �� 5       �@�Cursor$
 Hand��6'   �� 5       � �� 5      �� 5      " ��6&   .R�5      �� #��z��6!   $ 6��6K   ._�5      �� $��Center=�6/   $��Center=�6L   5      5      5       5      :� 5      $ Button.MouseEnter��6   [�5      �� 5      .��5      �� .��5   "   �� $1	 +(Button.Background).(SolidColorBrush.Color)�61   $
 #4f9dddX�5   !   $ 0:0:0.1D�6.   $ HoldEnd=�6A   6Z   5#      5$      5&      :� 5'      $ Button.MouseLeave��6   [�5(      �� 5)      .��5*      �� .��5+   "   �� $1	 +(Button.Background).(SolidColorBrush.Color)�61   $
 #2983ccX�5,   !   $ 0:0:0.1D�6.   6C   5.      5/      51      :� 52      $ Button.Click��6   [�53      �� 54      .��55      �� .��56   "   W� $	 (Button.Opacity)�57      $ 1X�58      $	 0.8X�6   $ 0:0:0.2D�6    . 6(   59      5:      5<      5>      5?      .��5@      � 
�������.+�5A   
   �� $
��Left=�6   $��20��6+   $��10,1,0,0q�67   $	��Top=�6I   $��22��6a   $��	/icon.ico��6l    J� OpacityMask 5B      �� 5C       �� ImageSource$ /update.png��6    j� Stretch$ Uniform=�67   5E      �� 5F   
   $��在线升级��6   $
��Left=�6   $��	40,-4,0,0q�6:   $	��Top=�6M   $	��177��6e   $��15(�6q   $��34��6   �� 5G   
   $��您已经是最新版本��6   $
��Left=�6#   $��
138,88,0,0q�6>   $	��Top=�6R   $	��286��6j   $��20(�6v   ��5H      �� 5I      5K      �� 5L   
   $
��Left=�6   $	��142��6+   $��154,158,0,0q�68   $	��Top=�6M   $	��151��6e   $��/update.png��6q   �� 5M   
   -   5         ��Name$ btnOK��5M      $��好的��6    #��[  6-   $��Microsoft YaHei UI)�6P   $��15(�6p   $��	0,477,0,0q�6~   $	��212��6�   $��35��6�   $��Center=�6�   $	��Top=�6�    �� 	ClickMode$ Press=�6�   5O      �� 5P   
   -   5         ��Name$ 
labversion��5P      $��最新版本��6$   $��Center=�63   $��	0,382,0,0q�6P   $	��Top=�6c   $	��286��6{   $��20(�6�   $��Center=�6�   $��Center=�6�   ��5Q      �� 5R      5T      5U      5V      