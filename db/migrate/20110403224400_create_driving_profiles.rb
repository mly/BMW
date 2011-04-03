class CreateDrivingProfiles < ActiveRecord::Migration
  def self.up
    create_table :driving_profiles do |t|
      t.int :id
      t.string :user_name
      t.int :mileage
      t.int :redlight_count
      t.float :mpg
      t.int :carma_points

      t.timestamps
    end
  end

  def self.down
    drop_table :driving_profiles
  end
end
