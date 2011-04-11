class DrivingProfileController < ApplicationController
      def list
      	  @profiles = DrivingProfile.find(:all)
      end
      
      def show
      	  @profile = DrivingProfile.find(params[:id])
      end
      
      def new
      	  @profile = DrivingProfile.new
      end

      def index
      	  create
      end

      def create

      	  # TODO: decode from JSON
      	  @profile = DrivingProfile.new(params[:driving_profile])

	  @profile.user_name = params[:user_name]
	  @profile.mileage = params[:mileage]
	  @profile.redlight_count = params[:redlight_count]
	  @profile.mpg = params[:mpg]
	  @profile.carma_points = params[:carma_points]
	  
	  if @profile.save
	     redirect_to :action => 'list'
	  end
      end

      def delete
      	  DrivingProfile.find(params[:id]).destroy
	  redirect_to :action => 'list'
      end

end
