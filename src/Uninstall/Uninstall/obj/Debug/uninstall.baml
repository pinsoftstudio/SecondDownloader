   M S B A M L   `   `   `  ����@  <setup, Version=1.0.0.0, Culture=neutral, PublicKeyToken=nullclr-namespace:setupsetup  5          setup.uninstall   5      R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5      R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5      Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5      @d2http://schemas.microsoft.com/expression/blend/2008     5      %localclr-namespace:setup     5        N� Title$  	uninstall��5       � 	Resources 5	       �� 
TargetType   	submitbtn �� Property �� Value �� 
TargetType �� CornerRadius �� Triggers :� RoutedEvent	 �� TargetProperty	
 �� To g� Duration g� FillBehavior W� From	 W� To g� AutoReverse  btn��%Y  &	        &	 %    �� 5
   
   " ��6   .�5      ��  � ��
 �����6+   �� 5       � �� �#2983cc6+   �� 5       �@�Cursor$
 Hand��6'   �� 5       � �� 5      �� 5      " ��6&   .R�5      �� #��z��6!   $ 6��6K   ._�5      �� $��Center=�6/   $��Center=�6L   5      5      5       5      :� 5      $ Button.MouseEnter��6   [�5      �� 5      .��5      �� .��5   "   �� $1	 +(Button.Background).(SolidColorBrush.Color)�61   $
 #4f9dddX�5   %   $ 0:0:0.1D�62   $ HoldEnd=�6E   6^   5"      5#      5%      :� 5&      $ Button.MouseLeave��6   [�5'      �� 5(      .��5)      �� .��5*   "   �� $1	 +(Button.Background).(SolidColorBrush.Color)�61   $
 #2983ccX�5+   %   $ 0:0:0.1D�62   6G   5-      5.      50      :� 51      $ Button.Click��6   [�52      �� 53      .��54      �� .��55   "   W� $	 (Button.Opacity)�56      $ 1X�57      $	 0.8X�6   $ 0:0:0.2D�6    . 6,   58      59      5;      5=      �� 5>   
   " ��6   .�5?      ��  � �� �#0006+   �� 5@       � �� �#ddd6+   �� 5A       �@�Cursor$
 Hand��6'   �� 5B       � �� 5C      �� 5D      " ��6&   .R�5E      �� #��z��6!   $ 6��6K   ._�5F      �� $��Center=�6/   $��Center=�6L   5G      5H      5J       5K      :� 5L      $ Button.MouseEnter��6   [�5M      �� 5N      .��5O      �� .��5P   "   �� $1	 +(Button.Background).(SolidColorBrush.Color)�61   $
 #e7e7e7X�5Q   %   $ 0:0:0.1D�62   $ HoldEnd=�6E   6^   5V      5W      5Y      :� 5Z      $ Button.MouseLeave��6   [�5[      �� 5\      .��5]      �� .��5^   "   �� $1	 +(Button.Background).(SolidColorBrush.Color)�61   $

 #dddX�5_   %   $ 0:0:0.1D�6/   6D   5a      5b      5d      :� 5e      $ Button.Click��6   [�5f      �� 5g      .��5h      �� .��5i   "   W� $	 (Button.Opacity)�5j      $ 1X�5k      $	 0.7X�6   $ 0:0:0.2D�6    . 6,   5l      5m      5o      5q      5r      .��5s      � 
�������.+�5t   
   �� $
��Left=�6   $	��111��6+   $��Center=�68   $	��115��6S   $��	/logo.png��6_   $��	55,0,0,40q�6r    J� OpacityMask 5u      �� 5v       �� ImageSource$ 	/logo.png��6    j� TileMode$
 None=�65    j� Stretch$ Uniform=�6E   5x      �� 5y   
   $��SecondDownloader��6   $
��Left=�6+   $��
186,0,0,80q�6F   $��Center=�6Z   $��Microsoft YaHei UI)�6u   $��25(�6�   �� 5z   
   $��正在卸载 ...��6   $
��Left=�6#   $��188,34,0,10q�6>   $��Center=�6S   $��Microsoft YaHei UI)�6n   $��15(�6�   �� 5{   
   $ ��Developed by PinsoftStudio��6   $
��Left=�65   $��
188,0,0,24q�6P   $��Center=�6d   $��Cascadia Code)�6   � 5|   
   -   5         �Name$ pb��5|      $��19��6"   $��
10,0,10,10q�6.   $��Bottom=�6B   ���	#FF2983CC���#eee��6�   Z� �� 5}   
   $��27��6   $��6,0,6,6q�6    $��Bottom=�61   
�������$��4��6[    �� RadiusX$ 9��6o    �� RadiusY$	 8.7��6{   5      5�      