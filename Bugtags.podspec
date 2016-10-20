Pod::Spec.new do |s|
  s.name         = "Bugtags"
  s.version      = "2.0.1"
  s.summary      = "Bug reporting for mobile apps, improve your app anytime, anywhere. Learn more at http://bugtags.com."
  s.homepage     = "http://bugtags.com/"
  s.license      = {
      :type => 'Commercial',
      :text => <<-LICENSE
                Copyright (C) 2016 Bugtags.
                Permission is hereby granted to use this framework as is, modification are not allowed.
                All rights reserved.
        
        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
        THE SOFTWARE.
      LICENSE
    }
  s.author              = { "Bugtags" => "dev@bugtags.com" }
  s.platform            = :ios, '6.0'
  s.source              = { :git => "https://github.com/bugtags/Bugtags-iOS.git", :tag => s.version.to_s }
  s.default_subspec     = 'Core'

  s.subspec 'Core' do |ss|
    ss.source_files        = 'Bugtags.framework/Versions/A/Headers/*.{h}'
    ss.resources           = 'Bugtags.bundle'
    ss.preserve_paths      = 'Bugtags.framework/*', 'Bugtags.bundle'
    ss.frameworks          = 'UIKit', 'ImageIO', 'AVFoundation', 'SystemConfiguration', 'CoreLocation', 'Security', 'CFNetwork', 'Bugtags'
    ss.xcconfig            = { 'FRAMEWORK_SEARCH_PATHS' => '"$(PODS_ROOT)/Bugtags/"', 'OTHER_LDFLAGS' => '-ObjC' }
    ss.requires_arc        = true
  end

  s.subspec 'BugtagsInsta' do |ss|
    ss.dependency 'Bugtags/Core'
    ss.dependency 'BugtagsInsta'
  end

  s.subspec 'Hotfix' do |ss|
    ss.dependency 'Bugtags/Core'
    ss.dependency 'JSPatch'
  end
end