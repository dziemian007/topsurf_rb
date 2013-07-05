#!/usr/bin/env ruby -rubygems
$LOAD_PATH.unshift(File.dirname(__FILE__))

require 'ffi'
require 'topsurf'
require 'pry'

IMAGES = ['compare1.jpg', 'compare2.jpg', 'compare3.jpg', 'compare4.jpg']
DESCRIPTORS = []

t = Topsurf.new

unless t.Initialize(256, 100)
  puts "Topsurf.Initialize failed"
  return
end

unless t.LoadDictionary('dict')
  puts "Topsurf.LoadDictionary failed"
  t.Terminate
  return
end

IMAGES.each_with_index do |img, i|
  DESCRIPTORS[i] = t.ExtractDescriptor(img)
end

distance = t.CompareImages('compare1.jpg', 'compare2.jpg', 'TOPSURF_COSINE');
puts "Comparing compare1.jpg and compare2.jpg using cosine normalized difference: #{distance}\n"
distance = t.CompareImages('compare1.jpg', 'compare3.jpg', 'TOPSURF_COSINE');
puts "Comparing compare1.jpg and compare3.jpg using cosine normalized difference: #{distance}\n"
distance = t.CompareImages('compare1.jpg', 'compare4.jpg', 'TOPSURF_COSINE');
puts "Comparing compare1.jpg and compare4.jpg using cosine normalized difference: #{distance}\n\n"

distance = t.CompareImages('compare1.jpg', 'compare2.jpg', 'TOPSURF_ABSOLUTE');
puts "Comparing compare1.jpg and compare2.jpg using absolute normalized difference: #{distance}\n"
distance = t.CompareImages('compare1.jpg', 'compare3.jpg', 'TOPSURF_ABSOLUTE');
puts "Comparing compare1.jpg and compare3.jpg using absolute normalized difference: #{distance}\n"
distance = t.CompareImages('compare1.jpg', 'compare4.jpg', 'TOPSURF_ABSOLUTE');
puts "Comparing compare1.jpg and compare4.jpg using absolute normalized difference: #{distance}\n\n"

#// Comparing descriptors using cosine normalized difference...
#//  the distance between image compare1.jpg and compare2.jpg is 0.0239710808
#//  the distance between image compare1.jpg and compare3.jpg is 0.5961593390
#//  the distance between image compare1.jpg and compare4.jpg is 0.9737141132
#// Comparing descriptors using absolute difference...
#//  the distance between image compare1.jpg and compare2.jpg is 0.3352426887
#//  the distance between image compare1.jpg and compare3.jpg is 5.5821442604
#//  the distance between image compare1.jpg and compare4.jpg is 5.8356685638

res = t.SaveDescriptor('compare1.jpg', 'descriptor1.surf')
res = t.SaveDescriptor('compare2.jpg', 'descriptor2.surf')
res = t.SaveDescriptor('compare3.jpg', 'descriptor3.surf')
res = t.SaveDescriptor('compare4.jpg', 'descriptor4.surf')

distance = t.CompareDescriptors('descriptor1.surf', 'descriptor2.surf', 'TOPSURF_COSINE');
puts "Comparing descriptor1.surf and descriptor2.surf using cosine normalized difference: #{distance}\n"
distance = t.CompareDescriptors('descriptor1.surf', 'descriptor3.surf', 'TOPSURF_COSINE');
puts "Comparing descriptor1.surf and descriptor3.surf using cosine normalized difference: #{distance}\n"
distance = t.CompareDescriptors('descriptor1.surf', 'descriptor4.surf', 'TOPSURF_COSINE');
puts "Comparing descriptor1.surf and descriptor4.surf using cosine normalized difference: #{distance}\n\n"

distance = t.CompareDescriptors('descriptor1.surf', 'descriptor2.surf', 'TOPSURF_ABSOLUTE');
puts "Comparing descriptor1.surf and descriptor2.surf using absolute normalized difference: #{distance}\n"
distance = t.CompareDescriptors('descriptor1.surf', 'descriptor3.surf', 'TOPSURF_ABSOLUTE');
puts "Comparing descriptor1.surf and descriptor3.surf using absolute normalized difference: #{distance}\n"
distance = t.CompareDescriptors('descriptor1.surf', 'descriptor4.surf', 'TOPSURF_ABSOLUTE');
puts "Comparing descriptor1.surf and descriptor4.surf using absolute normalized difference: #{distance}\n\n"












t.Terminate
